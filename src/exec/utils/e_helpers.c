/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:17 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:25:30 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/builtins.h"
#include "../../../includes/signals.h"
#include <sys/stat.h>
#include <errno.h>

void	assign_code(pid_t pid, int *status, t_exec_utils *util)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		util->code = WEXITSTATUS(*status);
	else
		util->code = EXIT_FAILURE;
}

int	check_access(char *path, t_exec_utils *util)
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
	return (0);
}

int	check_echo(t_ast_node *node, t_exec_utils *util, t_env **env,
			char *path)
{
	int		status;
	pid_t	pid;

	(void)env;
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
			assign_code(pid, &status, util);
			free(path);
			return (1);
		}
	}
	return (0);
}

int	builtins_one(t_ast_node *node, t_exec_utils *util, t_env **env,
			char *path)
{
	char	*oldpwd;

	(void)env;
	if (!ft_strcmp(node->args[0], "exit"))
	{
		if (handle_exit(util, node))
		{
			free(path);
			return (1);
		}
	}
	if (!ft_strcmp(node->args[0], "cd"))
	{
		oldpwd = getcwd(NULL, 0);
		change_dir(util, node->args);
		if (oldpwd)
			modify_oldpwd(&util->env, oldpwd);
		modify_pwd(&util->env);
		free(path);
		return (1);
	}
	return (0);
}

int	builtins_two(t_ast_node *node, t_exec_utils *util, t_env **env,
			char *path)
{
	if (!ft_strcmp(node->args[0], "pwd"))
	{
		exec_pwd(node->args, &util);
		free(path);
		return (1);
	}
	if (!ft_strcmp(node->args[0], "unset"))
	{
		exec_unset(env, node->args);
		util->code = 0;
		free(path);
		return (1);
	}
	if (!ft_strcmp(node->args[0], "export"))
	{
		exec_export(env, util, node->args);
		free(path);
		return (1);
	}
	return (0);
}
