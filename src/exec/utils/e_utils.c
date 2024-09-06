/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:16:27 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 19:04:15 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"

char	*my_getenv(char *name, t_env *env_ll)
{
	t_env	*curr;

	curr = env_ll;
	while (curr)
	{
		if (!(ft_strcmp(curr->key, name)))
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

char	*get_path(char **s_cmd, t_env **env_ll)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	*path;

	i = -1;
	path = my_getenv("PATH", (*env_ll));
	if (!path)
		return (NULL);
	allpath = ft_split(path, ':');
	if (!allpath)
		return (NULL);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			free_split(allpath);
			return (exec);
		}
	}
	free_split(allpath);
	return (NULL);
}



void	handle_doc(char *lim, int pipefd[2])
{
	char	*line;
	int		flag;

	flag = 1;
	while (flag)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			free(line);
			flag -= flag;
			close(pipefd[1]);
			return ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
}
