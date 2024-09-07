/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:26:33 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 15:19:42 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_lex_ll	*l_lstnew(int id)
{
	t_lex_ll	*node;

	node = malloc(sizeof(t_lex_ll));
	if (!node)
		return (NULL);
	node->id = id;
	node->next = NULL;
	node->lexer = NULL;
	return (node);
}

t_env	*env_lstnew(char *key, char *value, int hidden)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->hidden = hidden;
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
