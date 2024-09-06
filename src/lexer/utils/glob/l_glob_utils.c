/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_glob_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 18:06:16 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include <dirent.h>

int	l_glob_match(const char *pattern, const char *string)
{
	while (*pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (1);
			while (*string)
			{
				if (l_glob_match(pattern, string))
					return (1);
				string++;
			}
			return (0);
		}
		else
		{
			if (*pattern != *string)
				return (0);
			pattern++;
			string++;
		}
	}
	return (*string == '\0');
}

void	l_handler_wildcards(t_token *token, int count, char **glob_list)
{
	t_token	*store;
	int		i;

	i = 0;
	store = token->next;
	free(token->value);
	token->value = ft_calloc(1, ft_strlen(glob_list[0]) + 1);
	ft_strcpy(token->value, glob_list[0]);
	free(glob_list[0]);
	while (++i < count)
	{
		token->next = ft_calloc(1, sizeof(t_token));
		init_token(token->next, ft_strlen(glob_list[i]), token->id);
		token = token->next;
		token->type = TOKEN;
		ft_strcpy(token->value, glob_list[i]);
		free(glob_list[i]);
	}
	free(glob_list);
	token->next = store;
}

size_t	l_glob_count(const char *pattern)
{
	struct dirent	*entry;
	DIR				*dir;
	int				count;

	count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	if (!dir)
	{
		perror("opendir");
		return (0);
	}
	while ((entry))
	{
		if (l_glob_match(pattern, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}
