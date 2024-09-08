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
#include "../../../includes/signals.h"

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

char *get_path(char **s_cmd, t_env **env_ll)
{
	int i;
	char *exec;
	char **allpath;
	char *path_part;
	char *path;
	char *result;

	result = NULL;
	path = my_getenv("PATH", (*env_ll));
	if (!path)
		return (NULL);
	allpath = ft_split(path, ':');
	i = 0;
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			result = exec;
			break;
		}
		free(exec);
		i++;
	}
	free_split(allpath);
	return (result);
}

void	handle_doc(char *lim, int pipefd[2])
{
	char		*line;
	int		flag;

	flag = 1;
	while (flag)
	{
		line = get_next_line(STDIN_FILENO);
		signal(SIGINT, sigint_heredoc);
		if (g_mini_code == 52)
		{
			free(line);
			flag -= flag;
			close(pipefd[1]);
			return ;
		}
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

int	get_list_length(t_env *head)
{
	int length;

	length = 0;
	while (head != NULL)
	{
		length++;
		head = head->next;
	}
	return (length);
}

char	**allocate_array(int size)
{
	char	**arr;

	arr = malloc((size + 1) * sizeof(char *));
	arr[size] = NULL;
	return (arr);
}

static char	*create_key_value_string(char *key, char *value)
{
	size_t	key_len;
	size_t	value_len;
	size_t	total_len;
	char	*str;

	if (key)
		key_len = ft_strlen(key);
	if (value)
		value_len = ft_strlen(value);
	total_len = key_len + value_len + 2;
	str = malloc(total_len * sizeof(char));
	ft_strcpy(str, key);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

void	copy_list_to_array(t_env *head, char **arr)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		arr[i] = create_key_value_string(head->key, head->value);
		head = head->next;
		i++;
	}
}
