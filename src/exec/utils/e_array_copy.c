/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_array_copy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:15:22 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 08:17:53 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/signals.h"
#include "../../../includes/lexer.h"

int	get_list_length(t_env *head)
{
	int	length;

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
	if (value && str)
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
