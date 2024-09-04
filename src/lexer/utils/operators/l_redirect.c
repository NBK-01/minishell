/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:27:11 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 18:04:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

void	l_tokenize_heredoc(t_lexer *lex, t_token **token, int *state, int type)
{
	int	len;

	len = ft_strlen(lex->util->input);
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	(*token)->value[lex->util->j++] = type;
	(*token)->type = type;
	if (type == TYPE_LSHIFT)
		(*state) = IN_HEREDOC;
	else if (type == TYPE_RSHIFT)
		(*state) = IN_APPEND;
}

void	l_handler_skip(t_lexer *lex, t_token **token, int type, int **state)
{
	size_t	len;

	len = ft_strlen(lex->util->input);
	(*token)->value[lex->util->j] = '\0';
	(*token)->next = ft_calloc(1, sizeof(t_token));
	if ((*token)->next == NULL)
		return ;
	init_token((*token)->next, len - lex->util->i, (*token)->id);
	*token = (*token)->next;
	lex->util->j = 0;
	**state = STATE_ANY;
}

void	l_handler_heredoc(t_lexer *lex, t_token **token, int type, int *state)
{
	size_t	len;

	len = ft_strlen(lex->util->input);
	if (type == TYPE_LSHIFT)
	{
		(*token)->value[lex->util->j++] = '<';
		(*token)->value[lex->util->j] = '\0';
		(*token)->type = TYPE_HEREDOC;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
		*state = STATE_ANY;
	}
	else if (type != TYPE_LSHIFT)
	{
		l_handler_skip(lex, token, type, &state);
		l_tokenize(lex, token, type, state);
	}
}

void	l_handler_append(t_lexer *lex, t_token **token, int type, int *state)
{
	size_t	len;

	len = ft_strlen(lex->util->input);
	if (type == TYPE_RSHIFT)
	{
		(*token)->value[lex->util->j++] = '>';
		(*token)->value[lex->util->j] = '\0';
		(*token)->type = TYPE_APPEND;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
		*state = STATE_ANY;
	}
	else if (type != TYPE_RSHIFT)
	{
		l_handler_skip(lex, token, type, &state);
		l_tokenize(lex, token, type, state);
	}
}
