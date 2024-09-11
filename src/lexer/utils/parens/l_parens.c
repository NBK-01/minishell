/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_parens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:10:31 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/10 15:14:14 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

static void	close_token(t_lexer **lex, t_token **token)
{
	int	len;

	len = ft_strlen((*lex)->util->input);
	if ((*lex)->util->j > 0)
	{
		(*token)->value[(*lex)->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
		(*token) = (*token)->next;
		(*lex)->util->j = 0;
	}
}

static void	apply_recur(t_lexer **lex, t_token **token, int *state, int type)
{
	(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
	(*token)->type = type;
	(*state) = IN_PARAN;
	(*lex)->util->input_ptr++;
	(*token)->sub_lexer = malloc(sizeof(t_lexer));
	(*token)->sub_lexer->util = malloc(sizeof(t_lex_utils));
	(*token)->sub_lexer->util->rec_count = (*lex)->util->rec_count + 1;
	(*lex)->c_token = malloc(sizeof(t_token));
	init_lexer((*lex)->util->input_ptr, &(*token)->sub_lexer,
		&(*lex)->c_token, (*lex)->util->env);
	(*lex)->c_token = (*token)->sub_lexer->token_list;
	(*lex)->util->i += (*token)->sub_lexer->util->i;
	(*lex)->util->input_ptr += (*token)->sub_lexer->util->i;
}

int	handle_paren(t_lexer **lex, t_token **token, int *state, int type)
{
	if (type == TYPE_RPAREN && (*lex)->util->rec_count > 0)
		return (1);
	if (type == TYPE_LPAREN)
	{
		close_token(lex, token);
		apply_recur(lex, token, state, type);
		if (*(*lex)->util->input_ptr == ')' && (*state) == IN_PARAN)
		{
			(*state) = STATE_ANY;
			(*token)->value[(*lex)->util->j++] = TYPE_RPAREN;
			(*token)->value[(*lex)->util->j] = '\0';
			(*lex)->util->i++;
		}
	}
	return (0);
}
