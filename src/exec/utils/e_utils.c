/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:27 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:25:58 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/signals.h"
#include "../../../includes/lexer.h"

static int	path_helper(char *exec, char **result)
{
	if (access(exec, F_OK | X_OK) == 0)
	{
		*result = exec;
		return (1);
	}
	return (0);
}

char	*get_path(char **s_cmd, t_env **env_ll, char *result)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	*path;

	result = NULL;
	path = my_getenv("PATH", (*env_ll));
	if (!path)
		return (NULL);
	allpath = ft_split(path, ':');
	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (path_helper(exec, &result))
			break ;
		free(exec);
	}
	free_split(allpath);
	return (result);
}

static void	doc_expand(char *line, int pipefd[2], t_env *env, int expand)
{
	if (expand == 2)
		line = line;
	else
		line = expand_variables(line, 1, env);
	write(pipefd[1], line, ft_strlen(line));
	free(line);
}

static void	end_heredoc(char *line, int *flag, int pipefd[2])
{
	free(line);
	*flag -= *flag;
	close(pipefd[1]);
}

void	handle_doc(t_ast_node *node, int pipefd[2], t_env *env)
{
	char		*line;
	int			flag;
	char		*lim;

	flag = 1;
	lim = node->in;
	while (flag)
	{
		line = get_next_line(STDIN_FILENO);
		if (g_mini.mini_code == 130 || !line)
		{
			end_heredoc(line, &flag, pipefd);
			return ;
		}
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			end_heredoc(line, &flag, pipefd);
			return ;
		}
		doc_expand(line, pipefd, env, node->here_doc);
	}
}
