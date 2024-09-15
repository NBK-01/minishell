/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:11:06 by nbk               #+#    #+#             */
/*   Updated: 2024/09/09 03:11:12 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "./minishell.h"

typedef enum e_token_type
{
	TYPE_MINUS = '-',
	TYPE_PLUS = '+',
	TYPE_SPACE = 32,
	TYPE_WORD = -42,
	TYPE_SEMI = ';',
	TYPE_LSHIFT = '<',
	TYPE_RSHIFT = '>',
	TYPE_PIPE = '|',
	TYPE_DQUOTE = 34,
	TYPE_QUOTE = 39,
	TYPE_LPAREN = '(',
	TYPE_RPAREN = ')',
	TYPE_AMPERSAND = '&',
	TYPE_AND = 5000,
	TYPE_OR = 5001,
	TYPE_DOLLAR = '$',
	TYPE_EQUAL = '=',
	TYPE_NEWLINE = '\n',
	TYPE_ESC = '\\',
	TYPE_EOF = '\0',
	TYPE_NULL = 0,
	TOKEN = -42,
	TYPE_APPEND,
	TYPE_HEREDOC,
	TYPE_TAB = '\t',
	IN_QUOTES,
	IN_DQUOTES,
	IN_ESC,
	STATE_ANY,
	IN_AND,
	IN_OR,
	IN_HEREDOC,
	IN_APPEND,
	IN_PARAN,
}	t_token_type;

int		l_token_count(t_lexer *lex, t_token *token, t_env *env);
void	free_token_ll(t_token *token);
int		l_assign_type(char c);
int		return_whitespaces(char c);
int		return_operators(char c);
int		count_dash(char *args);
int		return_literals(char c);
void	l_terminate_token(t_lexer *lex, t_token **token);
void	init_token(t_token *token, int n, int id);

#endif
