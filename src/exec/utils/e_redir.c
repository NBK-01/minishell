/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:02:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 14:59:29 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/builtins.h"
#include "../../../includes/signals.h"
#include <sys/stat.h>
#include <errno.h>

void	check_in(t_ast_node *node, int pipefd[2], t_exec_utils *util)
{
	int	fd_in;

	if (node->in)
	{
		if (node->exit)
			exit(node->exit);
		if (node->here_doc)
		{
			pipe(pipefd);
			handle_doc(node, pipefd, util->env);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		else
		{
			fd_in = open(node->in, O_RDONLY);
			if (fd_in < 0)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
	}
}

void	e_redirection(t_ast_node *node, t_exec_utils *util)
{
	int	fd_out;
	int	pipefd[2];

	check_in(node, pipefd, util);
	if (node->out)
	{
		if (node->exit)
			exit(node->exit);
		if (node->append)
			fd_out = open(node->out, O_WRONLY | O_APPEND | O_CREAT, 0644);
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

int	check_path(char *path, t_exec_utils *util)
{
	struct stat	statbuf;

	if (path && stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putendl_fd(" Is a directory", 2);
			util->code = 126;
			util->exit_code = 126;
			free(path);
			return (1);
		}
	}
	return (0);
}
