/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:49:58 by mhabbal           #+#    #+#             */
/*   Updated: 2024/09/16 15:27:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/ast.h"
#include "../../../includes/token.h"
#include "../../../includes/execute.h"
#include <fcntl.h>
#include <errno.h>

size_t	array_size(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

void	realloc_args(t_ast_node *node, char *input)
{
	size_t	len;
	char	**copy;
	int		i;

	i = 0;
	len = array_size(node->args);
	copy = malloc((len + 2) * sizeof(char *));
	while (node->args[i])
	{
		copy[i] = ft_strdup(node->args[i]);
		i++;
	}
	copy[i] = ft_strdup(input);
	i++;
	copy[i] = 0;
	free(node->args);
	node->args = copy;
}

void	here_doc_handler(t_ast_node *node, t_exec_utils **util)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (node && node->args && node->args[0] && !ft_strcmp(node->args[0], "()"))
		here_doc_handler(node->tree_link->branch, util);
	else if (node->here_doc)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
			exit (0);
		if (pid == 0)
		{
			handle_doc(node, pipefd, (*util)->env, *util);
		}
		waitpid(pid, &status, 0);
		close(pipefd[1]);
		node->fd_here_doc = pipefd[0];
	}
	if (node->left)
		here_doc_handler(node->left, util);
	if (node->right)
		here_doc_handler(node->right, util);
}
