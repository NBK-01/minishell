/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:17 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 17:08:28 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/builtins.h"
#include "../../includes/signals.h"
#include <sys/stat.h>
#include <errno.h>

int	e_traverse_tree(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	char	*path;
	char	*hello;

	if (!node)
		return (1);
	if (node->type == AST_COMMAND)
	{
		if (node && node->args && node->args[0])
		{
			if (!ft_strncmp(node->args[0], "/", 1) || !ft_strncmp(node->args[0], "./", 2))
				path = ft_strdup(node->args[0]);
			else
				path = get_path(node->args, env);
			return (e_simple_command(node, util, env, path));
		}
	}
	else if (node->type == AST_PIPE)
		e_pipeline(node, util, env);
	else if (node->type == AST_AND)
		e_operator_and(node, util, env);
	else if (node->type == AST_OR)
		e_operator_or(node, util, env);
	else
		printf("node type error");
	return (util->code);
}

void	e_operator_and(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util, env);
	else
		e_traverse_tree(node->left, util, env);
	if (util->code == EXIT_SUCCESS)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util, env);
		else
			e_traverse_tree(node->right, util, env);
	}
	else if (util->code == EXIT_FAILURE)
		return ;
}

void	e_operator_or(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util, env);
	else
		e_traverse_tree(node->left, util, env);
	if (util->code == EXIT_SUCCESS)
		return ;
	else if (util->code == EXIT_FAILURE)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util, env);
		else
			e_traverse_tree(node->right, util, env);
	}
}

void	e_pipeline(t_ast_node *node, t_exec_utils *util, t_env **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	(void)env;
	if (pipe(fd) == -1)
	{
		perror("pipe");
		util->code = EXIT_FAILURE;
		return ;
	}
	e_pipeline_parent(node, util, &pid1, fd);
	e_pipeline_child(node, util, &pid2, fd);
	close(fd[0]);
	close(fd[1]);
	e_pipeline_status(pid1, pid2, &status, util);
}



int e_simple_command(t_ast_node *node, t_exec_utils *util, t_env **env, char *path)
{
    struct stat statbuf;
    char **array;
    pid_t pid;
    int status;

    if (path && stat(path, &statbuf) == 0)
    {
        if (S_ISDIR(statbuf.st_mode))
        {
            ft_putendl_fd(" Is a directory", 2);
            util->code = 126;
            util->exit_code = 126;
            free(path);
            return (126);
        }
    }
    
    if (path)
    {
        if (access(path, X_OK) != 0)
        {
            if (errno == EACCES)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(path, 2);
                ft_putendl_fd(": Permission denied", 2);
                util->code = 126;
                util->exit_code = 126;
                free(path);
                return (126);
            }
            else if (errno == ENOENT)
            {
                ft_putstr_fd("minishell: ", 2);
                ft_putstr_fd(path, 2);
                ft_putendl_fd(": No such file or directory", 2);
                util->code = 127;
                free(path);
                return (127);
            }
        }
    }

    if (!ft_strcmp(node->args[0], "echo"))
    {
        pid = fork();
        if (pid == 0)
        {
            e_redirection(node, util);
            exec_echo(node, &util);
            exit(0);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
            util->code = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
            util->exit_code = util->code;
            free(path);
            return (util->code);
        }
        else
        {
            perror("fork");
            free(path);
            exit(EXIT_FAILURE);
        }
    }

    if (!ft_strcmp(node->args[0], "exit"))
    {
        if (handle_exit(util, node, (*env)))
        {
            free(path);
            return (util->code);
        }
    }
   if (!ft_strcmp(node->args[0], "cd"))
    {
        char *oldpwd = getcwd(NULL, 0);
        if (oldpwd)
        {
            change_dir(util, node->args);
            modify_oldpwd(&util->env, oldpwd);
	    free(oldpwd);
        }
        free(path);
        return (util->code);
    }
    if (!ft_strcmp(node->args[0], "pwd"))
    {
        exec_pwd(node->args, &util);
        free(path);
        return (util->code);
    }
    if (!ft_strcmp(node->args[0], "unset"))
    {
        exec_unset(env, node->args);
        util->code = 0;
        free(path);
        return (0);
    }
    if (!ft_strcmp(node->args[0], "export"))
    {
        exec_export(env, util, node->args);
        free(path);
        return (util->code);
    }
    pid = fork();
    if (pid == 0)
    {
	 if (!ft_strcmp(node->args[0], "env"))
	 {
        exec_env(env, node->args);
        free(path);
        exit (util->code);
    }

        e_redirection(node, util);
        if (path)
        {
	    array = allocate_array(get_list_length(*env));
            copy_list_to_array(*env, array);
            execve(path, node->args, array);
        }
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(node->args[0], 2);
        ft_putendl_fd(": command not found", 2);
        util->code = 127;
        exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        util->code = WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
        util->exit_code = util->code;
    }
    else
    {
        perror("fork");
        free(path);
        exit(EXIT_FAILURE);
    }

    free(path);
    return (util->code);
}

void	e_redirection(t_ast_node *node, t_exec_utils *util)
{
	int	fd_in;
	int	fd_out;
	int	pipefd[2];

	(void)util;
	if (node->in)
	{
		if (node->exit)
			exit(node->exit);
		if (node->here_doc)
		{
			g_mini_code = 10;
			pipe(pipefd);
			handle_doc(node->in, pipefd);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		else
		{
			fd_in = open(node->in, O_RDONLY);
			if (fd_in < 0)
			{
				perror("open input");
				exit(EXIT_FAILURE);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
	if (node->out)
	{
		if (node->exit)
			exit(node->exit);
		if (node->append)
		{
			fd_out = open(node->out, O_WRONLY | O_APPEND | O_CREAT , 0644);
		}
		else
			fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			ft_putendl_fd(" permission denied", 2);
			util->code = 1;
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
