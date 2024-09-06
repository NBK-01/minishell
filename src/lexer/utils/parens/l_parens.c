/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_parens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:10:31 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 18:11:47 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

int	handle_paren(t_lexer **lex, t_token **token, int *state, int type)
{
	int		len;
	t_token	*c_token;

	len = ft_strlen((*lex)->util->input);
	if (type == TYPE_RPAREN && (*lex)->util->rec_count > 0)
		return (1);
	if (type == TYPE_LPAREN)
	{
		if ((*lex)->util->j > 0)
		{
			(*token)->value[(*lex)->util->j] = '\0';
			(*token)->next = ft_calloc(1, sizeof(t_token));
			if ((*token)->next == NULL)
				return (0);
			init_token((*token)->next, len - (*lex)->util->i, (*token)->id);
			(*token) = (*token)->next;
			(*lex)->util->j = 0;
		}
		(*token)->value[(*lex)->util->j++] = TYPE_LPAREN;
		(*token)->type = type;
		(*state) = IN_PARAN;
		(*lex)->util->input_ptr++;
		(*token)->sub_lexer = ft_calloc(1, sizeof(t_lexer));
		(*token)->sub_lexer->util = malloc(sizeof(t_lex_utils));
		(*token)->sub_lexer->util->rec_count = (*lex)->util->rec_count + 1;
		c_token = malloc(sizeof(t_token));
		init_lexer((*lex)->util->input_ptr, &(*token)->sub_lexer,
			&c_token, (*lex)->util->env);
		(*lex)->util->i += (*token)->sub_lexer->util->i;
		(*lex)->util->input_ptr += (*token)->sub_lexer->util->i;
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
