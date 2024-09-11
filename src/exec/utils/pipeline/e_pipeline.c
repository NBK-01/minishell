/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_pipeline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:24 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/10 17:13:50 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/execute.h"
#include "../../../../includes/builtins.h"
#include "../../../../includes/signals.h"

void	e_pipeline_parent(t_ast_node *node, t_exec_utils *util,
							int *pid, int fd[2])
{
	int	code;

	(*pid) = fork();
	if ((*pid) == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (!ft_strcmp(node->left->args[0], "()"))
			code = e_traverse_tree(node->left->tree_link->branch,
					util, &util->env);
		else
			code = e_traverse_tree(node->left, util, &util->env);
		exit(code);
	}
	else if ((*pid) < 0)
	{
		perror("fork");
		util->code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	e_pipeline_child(t_ast_node *node, t_exec_utils *util, int *pid,
							int fd[2])
{
	int	code;

	(*pid) = fork();
	if ((*pid) == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (!ft_strcmp(node->right->args[0], "()"))
			code = e_traverse_tree(node->right->tree_link->branch,
					util, &util->env);
		else
			code = e_traverse_tree(node->right, util, &util->env);
		exit(code);
	}
	else if ((*pid) < 0)
	{
		perror("fork");
		util->code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

void	e_pipeline_status(int pid1, int pid2, int *status, t_exec_utils *util)
{
	waitpid(pid1, status, 0);
	if (WIFEXITED((*status)))
		util->code = WEXITSTATUS((*status));
	else
		util->exit_code = EXIT_FAILURE;
	waitpid(pid2, status, 0);
	if (WIFEXITED((*status)))
		util->code = WEXITSTATUS((*status));
	else
		util->exit_code = EXIT_FAILURE;
}

void	proccess_one(t_ast_node *node, t_exec_utils *util, t_env **env,
			char *path)
{
	char		**array;

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
