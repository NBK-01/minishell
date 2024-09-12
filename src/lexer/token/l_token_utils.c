/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:57:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/10 14:03:53 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/lexer.h"

void	free_token_ll(t_token *token)
{
	if (token)
	{
		if (token->sub_lexer)
			free_lexer(&token->sub_lexer);
		free(token->value);
		free_token_ll(token->next);
		if (token)
			free(token);
	}
}

int	l_assign_type(char c)
{
	if (c == ' ' || c == '\t' || c == '\\' || c == '\n')
		return (return_whitespaces(c));
	if (c == '|' || c == '<' || c == '>' || c == '&'
		|| c == ';')
		return (return_operators(c));
	if (c == 34 || c == 39 || c == '(' || c == ')')
		return (return_literals(c));
	if (c == 0)
		return (TYPE_NULL);
	else
		return (TYPE_WORD);
}

void	l_terminate_token(t_lexer *lex, t_token **token)
{
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		lex->util->j = 0;
	}
}
