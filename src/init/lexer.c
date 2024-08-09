/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:00 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/07 09:07:02 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/lexer.h"

t_token	*l_vars_init(char *input, t_lexer *lex, t_token *token)
{
	lex->token_list = malloc(sizeof(t_token));
	token = lex->token_list;
	lex->util->i = 0;
	lex->util->j = 0;
	lex->util->input = input;
	lex->util->input_ptr = input;
	lex->child = ft_calloc(1, sizeof(t_lex_ll));
	return (token);
}

void	init_token(t_token *token, int n, int id)
{
	token->value = ft_calloc(1, n + 1);
	token->value[0] = TYPE_NULL;
	token->type = TYPE_NULL;
	token->id = id + 1;
	token->next = NULL;
}

int	init_lexer(char *input, int id, t_lexer **lex, t_token **token)
{
	int	state;
	int	type;
	size_t	len;

	len = ft_strlen(input);
	state = STATE_ANY;
	(*token) = l_vars_init(input, (*lex), (*token));
	init_token((*token), len, id);
	while (*(*lex)->util->input_ptr) 
	{
		(*lex)->util->c = *(*lex)->util->input_ptr;
		type = l_assign_type((*lex)->util->c);
		if (l_tokenize((*lex), token, type, &state) == 1)
		{
			if ((*lex)->util->j > 0)
				(*token)->value[(*lex)->util->j] = '\0';
			return (l_token_count((*lex), (*token), type));
		}
		(*lex)->util->i++;
		(*lex)->util->input_ptr++;
	}
	if ((*lex)->util->j > 0)
		(*token)->value[(*lex)->util->j] = '\0';
	(*token) = (*lex)->token_list;
	return (l_token_count((*lex), (*token), type));
}
