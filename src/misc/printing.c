/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:06:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 17:06:27 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"
#include "../../includes/minishell.h"

static void	print_tokens(t_token *token_list, int id)
{
	while (token_list)
	{
		if (token_list->value)
		{
			if (id == 0)
				printf("MAIN LEVEL: %s\n", token_list->value);
			else
			{
				printf("CHILD LEVEL %d: %s\n", id, token_list->value);
			}
		}
		token_list = token_list->next;
	}
}

void	l_recursive_print(t_lexer *lex, int id)
{
	int				i;
	t_lex_ll		**child;

	i = 0;
	if (!lex)
		return ;
	if (lex->token_list)
		print_tokens(lex->token_list, id);
	if ((*lex->child))
	{
		while ((*lex->child))
		{
			child = lex->child;
			while ((*child))
			{
				if ((*child)->lexer)
					l_recursive_print((*child)->lexer, id + 1);
				(*child) = (*child)->next;
			}
			i++;
		}
	}
}
