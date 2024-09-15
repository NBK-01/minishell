/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:52:00 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 09:47:49 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/get_next_line.h"
#include <fcntl.h>

char	*special_char(char *str)
{
	char *temp;
	int 	i;

	i = 0;
	while (str[i] != '=')
		i++;
	temp = malloc((i + 1) * sizeof(char));
	i = 0;
	while (str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

void	get_pair(char	*str, char **key, char **value)
{
	char *temp;
	char *delim;
	char	*try;

	temp = ft_strdup(str);
	delim = ft_strdup(ft_strchr(temp, '='));
	try = special_char(str);
	if (delim != NULL)
	{
		*value = ft_strdup(delim + 1);
		// *delim = 0;
		*key = ft_strdup(try);
	}
	else
	{
		value = NULL;
		*key = ft_strdup(temp);
	}
	free(delim);
	free(temp);
	free(try);
}

char	*get_key(char *str)
{
	// char	*temp;
	char	*key;

	key = special_char(str);
	// free(temp);
	return (key);
}

char	*get_value(const char *str)
{
	char	*delim;
	char	*value;

	delim = ft_strchr(str, '=');
	if (delim != NULL)
		value = ft_strdup(delim + 1);
	else
		value = NULL;
	return (value);
}

void	add_special_env(t_env **env_ll)
{
	t_env	*new;
	int		fd;
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
		pid = split[3];
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

	i = -1;
	while (env[++i])
	{
		get_pair(env[i], &key, &value);
		new = env_lstnew(key, value, 0);
		env_lstadd_back(env_ll, new);
		free(value);
		free(key);
	}
	add_special_env(env_ll);
}
