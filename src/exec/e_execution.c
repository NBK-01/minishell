/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:17 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/26 16:28:13 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/builtins.h"

void	e_traverse_tree(t_ast_node *node, t_exec_utils *util)
{
	if (!node)
		return;
	if (node->type == AST_COMMAND)
		e_simple_command(node, util);
	else if (node->type == AST_PIPE)
		e_pipeline(node, util);
	else if (node->type == AST_AND)
		e_operator_and(node, util);
	else if (node->type == AST_OR)
		e_operator_or(node, util);
	else
		printf("node type error");
}

void	e_operator_and(t_ast_node *node, t_exec_utils *util)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util);
	else
		e_traverse_tree(node->left, util);
	if (util->code == EXIT_SUCCESS)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util);
		else
			e_traverse_tree(node->right, util);
	}
	else if (util->code == EXIT_FAILURE)
		return ;
}

void	e_operator_or(t_ast_node *node, t_exec_utils *util)
{
	if (!ft_strcmp(node->left->args[0], "()"))
		e_traverse_tree(node->left->tree_link->branch, util);
	else
		e_traverse_tree(node->left, util);
	if (util->code == EXIT_SUCCESS)
		return ;
	else if (util->code == EXIT_FAILURE)
	{
		if (!ft_strcmp(node->right->args[0], "()"))
			e_traverse_tree(node->right->tree_link->branch, util);
		else
			e_traverse_tree(node->right, util);
	}
}	

void e_pipeline(t_ast_node *node, t_exec_utils *util)
{
	int	fd[2];
	int	status;
	pid_t	pid1;
	pid_t	pid2;

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


void e_simple_command(t_ast_node *node, t_exec_utils *util)
{
    char *path;
    pid_t pid;
    int status;

    if (!ft_strcmp(node->args[0], "env"))
    {
        exec_env(&util->env, node->args);
        return;
    }
    if (!ft_strcmp(node->args[0], "unset"))
    {
        exec_unset(&util->env, node->args);
        return;
    }
    if (!ft_strcmp(node->args[0], "export"))
    {
        exec_export(&util->env, node->args[1]);
        return;
    }
	if (!ft_strcmp(node->args[0], "cd"))
	{
		change_dir(util, node->args);
		return ;
	}
    if (!ft_strncmp(node->args[0], "/", 1) || !ft_strncmp(node->args[0], "./", 2))
        path = ft_strdup(node->args[0]);
    else
        path = get_path(node->args, util->env);

    pid = fork();
    if (pid == 0)
    {
        e_redirection(node, util);
	execve(path, node->args, util->env->og);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(node->args[0], 2);
	exit(127);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            util->code = WEXITSTATUS(status); // General exit code
            util->exit_code = WEXITSTATUS(status); // Specific exit code from execve
        }
        else
        {
            util->code = EXIT_FAILURE;
            util->exit_code = EXIT_FAILURE;
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    free(path);
}

void	e_redirection(t_ast_node *node, t_exec_utils *util)
{
	int	fd_in;
	int	fd_out;
	int	pipefd[2];

	(void)util;
	if (node->in)
	{
		if (node->here_doc)
		{
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
		if (node->append)
		{
			fd_out = open(node->out, O_WRONLY | O_APPEND | O_CREAT , 0644);
		}
		else
			fd_out = open(node->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0)
		{
			perror("open output");
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}
