/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:36:11 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 09:01:47 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst == NULL)
		return ;
	while (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = ft_lstlast(*lst);
	end->next = new;
}

void	l_lstadd_back(t_lex_ll **lst, t_lex_ll *new)
{
	t_lex_ll	*end;

	if (lst == NULL)
		return ;
	while (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = l_lstlast(*lst);
	end->next = new;
}

void	env_lstadd_back(t_env **env, t_env *new)
{
	t_env	*end;

	if (env == NULL)
		return ;
	if (*env == NULL)
	{
		(*env) = new;
		return ;
	}
	end = env_lstlast(*env);
	end->next = new;
}

t_env	*ft_lstcpy(t_env **stack)
{
	t_env	*src;
	t_env	*dest;
	t_env	**temp;

	src = *stack;
	dest = NULL;
	temp = &dest;
	while (src)
	{
		*temp = (t_env *)malloc(sizeof(t_env));
		if (!*temp)
			return (NULL);
		if (src->key)
			(*temp)->key = ft_strdup(src->key);
		if (src->value != NULL)
			(*temp)->value = ft_strdup(src->value);
		else
			(*temp)->value = ft_strdup("");
		(*temp)->hidden = src->hidden;
		(*temp)->next = NULL;
		temp = &((*temp)->next);
		src = src->next;
	}
	return (dest);
}
