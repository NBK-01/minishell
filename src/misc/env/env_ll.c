/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:52:00 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 19:46:29 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/get_next_line.h"
#include <fcntl.h>

char	*get_key(char *str)
{
	char	*temp;
	char	*delim;
	char	*key;

	temp = ft_strdup(str);
	delim = ft_strchr(temp, '=');
	if (delim != NULL)
	{
		*delim = '\0';
		key = temp;
	}
	else
		key = temp;
	return (key);
}

char	*get_value(char *str)
{
	char	*delim;
	char	*value;

	delim = ft_strchr(str, '=');
	if (delim != NULL)
		value = delim + 1;
	else
		value = NULL;
	return (value);
}


void	add_special_env(t_env **env_ll)
{
	t_env	*new;
	int	fd;
	char	*line;
	char	**split;
	char	*pid;

	split = NULL;
	new = env_lstnew("?", "0", 2);
	env_lstadd_back(env_ll, new);
	fd = open("/proc/self/stat", O_RDONLY);
	line = get_next_line(fd);
	close(fd);
	if (line)
		split = ft_split(line, ' ');
	if (split)
	{
		pid = ft_strdup(split[3]);
		new = env_lstnew("$", pid, 2);
	}
	else
		new = env_lstnew("$", "123", 2);
	env_lstadd_back(env_ll, new);
	free_split(split);
	free(line);
}

void	copy_env(t_env **env_ll, char **env)
{
	int		i;
	char		*key;
	char		*value;
	t_env		*new;

	i = 0;
	while (env[i])
	{
		key = get_key(env[i]);
		value = get_value(env[i]);
		new = env_lstnew(key, value, 0);
		env_lstadd_back(env_ll, new);
		i++;
	}
	add_special_env(env_ll);
}
