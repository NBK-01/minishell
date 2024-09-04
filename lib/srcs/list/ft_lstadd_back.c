/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:36:11 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 15:19:39 by nbk              ###   ########.fr       */
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

	end = (*env);
	if (env == NULL || new == NULL)
		return ;
	if (*env == NULL)
	{
		(*env) = new;
		return ;
	}
	while (end->next)
		end = end->next;
	end->next = new;
}
