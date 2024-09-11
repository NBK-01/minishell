/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:17 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 14:46:04 by nkanaan          ###   ########.fr       */
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

	if (!node)
		return (1);
	path = NULL;
	if (node->type == AST_COMMAND)
	{
		if (node && node->args && node->args[0])
		{
			if (!ft_strncmp(node->args[0], "/", 1)
				|| !ft_strncmp(node->args[0], "./", 2))
				path = ft_strdup(node->args[0]);
			else
				path = get_path(node->args, env, path);
			return (e_simple_command(node, util, env, path));
		}
	}
	else if (node->type == AST_PIPE)
		e_pipeline(node, util, env);
	else if (node->type == AST_AND)
		e_operator_and(node, util, env);
	else if (node->type == AST_OR)
		e_operator_or(node, util, env);
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
	else if (util->code > 0)
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

int	e_simple_command(t_ast_node *node, t_exec_utils *util, t_env **env,
			char *path)
{
	pid_t		pid;
	int			status;

	if (check_path(path, util))
		return (util->code);
	if (path)
		if (access(path, X_OK) != 0)
			return (check_access(path, util));
	if (check_echo(node, util, env, path))
		return (util->code);
	if (builtins_one(node, util, env, path))
		return (util->code);
	if (builtins_two(node, util, env, path))
		return (util->code);
	signal_handler();
	signal_exec(node);
	pid = fork();
	if (pid == 0)
		proccess_one(node, util, env, path);
	else if (pid > 0)
		assign_code(pid, &status, util);
	signal_handler();
	free(path);
	return (util->code);
}
