/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:30:04 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 18:21:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void	l_tokenize_state(t_lexer *lex, t_token **token, int type, int **state)
{
	size_t	len;

	len = ft_strlen(lex->util->input);
	if ((**state) == IN_QUOTES || (**state) == IN_DQUOTES)
		l_state_handler_quote_exit(lex, token, type, *state);
	else if ((**state) == IN_AND)
	{
		l_handler_ampersand(lex, token, type, len);
		(**state) = STATE_ANY;
	}
	else if ((**state) == IN_HEREDOC)
		l_handler_heredoc(lex, token, type, *state);
	else if ((**state) == IN_APPEND)
		l_handler_append(lex, token, type, *state);
	else if ((**state) == IN_OR)
	{
		l_handler_pipe(lex, token, type, len);
		(**state) = STATE_ANY;
	}
}

void	l_term(t_lexer *lex, t_token **token, int type)
{
	if (type == TYPE_NULL)
		l_terminate_token(lex, token);
}

int	l_tokenize(t_lexer *lex, t_token **token, int type, int *state)
{
	int	len;

	len = ft_strlen(lex->util->input);
	if ((*state) == STATE_ANY)
	{
		if (type == TYPE_QUOTE || type == TYPE_DQUOTE)
			l_state_handler_quote_in(lex, token, type, state);
		if (type == TYPE_ESC || type == TYPE_WORD)
			l_tokenize_words(lex, (*token), type);
		else if (type == TYPE_SPACE || type == TYPE_SEMI || type == TYPE_EQUAL
			|| type == TYPE_PLUS)
			l_tokenize_next(lex, token, type, len);
		else if (type == TYPE_LSHIFT || type == TYPE_RSHIFT)
			l_tokenize_heredoc(lex, token, state, type);
		else if (type == TYPE_AMPERSAND)
			l_tokenize_ampersand(lex, token, state, type);
		else if (type == TYPE_PIPE)
			l_tokenize_pipe(lex, token, state, type);
		else if (type == TYPE_LPAREN || type == TYPE_RPAREN)
			return (handle_paren(&lex, token, state, type));
	}
	else if ((*state) != STATE_ANY)
		l_tokenize_state(lex, token, type, &state);
	return (0);
}
//////////////////// BRAINSTROM ///////////////////////
/* 
 * INIT LEXER => struct init and allocation + init_token()
 * LEX_NEXT (ITERATE WHEN TOKEN ASSIGNED) => iterate by index in 
 *					     struct
 *					       |
 *				   t_lexer *lexer->index += 1;			   
 * LEX_BY_ID => TBD TBD TBD 
 *
 * LEX_PEAK => SET FLAG TO PEAK = 0
 *		IF PEAK == 1 => look ahead in the str (INPUT).
 *		CHECK IF FLAG SET LOCAL OR IN STRUCT ??
 * -------------------------------------
 *  ASSIGN TOKENS => basic switch case (if else due to norme) 
 *		      Special cases:
 *				echo (TAKE ALL ARGS AFTER AS ONE TOKEN???)
 *				"|" (PIPE IN QUOTES)
 *				ALL QUOTES (DISREGARD FOR LEXER V1)
 *
 * COMMAND EXAMPLES: 
 *		"cat file1" => unkown cmd
 *		echo 'hello' | cat -e => hello$
 *		echo -n 'hello' | cat -e => hello
 * TOKEN---
 *	  |
 *	  => INIT_TOKEN = ALLOCATE MEMORY (CALLOC) + STRCUT INIT 
 *		=> ASSIGN_TOKEN ((TOKEN_TYPE) -- (TOKEN_VALUE))
 *			=> COMMAND + FILES SET AS STRING (WORD) TYPE TOK
 *
 * */
