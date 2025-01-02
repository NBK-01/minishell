/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 02:59:02 by nbk               #+#    #+#             */
/*   Updated: 2024/09/16 14:15:11 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "./minishell.h"
# include "./token.h"
# include <stdbool.h>

struct	s_synatx_tree;

typedef struct s_ast_utils
{
	char		*out;
	char		*in;
	char		*args;
	int			in_pipe;
	int			flag;
	int			append;
	int			here_doc;
	t_ast_node	*node;
	t_ast_node	*right;
	t_lexer		**sub;
	int			echo_flag;
	int			exit;
	int			flag1;
	int			flag2;
}	t_ast_utils;

void		parse_heredoc(t_token *token, t_ast_utils **util);
void		skip_token(t_token **tok, t_lexer **lex);
void		parse_heredoc(t_token *token, t_ast_utils **util);
void		init_parser(t_lexer **lexer, t_syntax_tree **tree);
void		p_expand_tree(t_ast_node *node);
t_ast_node	*p_build_tree(t_lexer **lex, t_token *token);
t_ast_utils	*p_init_vars(t_ast_utils **util);
char		*p_create_cmd_args(char *value, char *args);
int			p_parse_simple_command(t_ast_utils **util,
				t_lexer **lex, t_token *tok);
t_ast_node	*p_build_pipeline(t_lexer **lex, t_token *tok);
int			p_parse_pipeline(t_ast_utils **util, t_lexer **lex, t_token *tok);
int			p_parse_operators(t_ast_utils **util, t_lexer **lex, t_token **tok);
int			p_parse_redirect(t_ast_utils **util, t_lexer **lex, t_token **tok);
void		redirect_access(t_ast_utils **util);
void		redirect_access_in(t_ast_utils **util);
t_ast_node	*p_build_simple_command(t_ast_utils *util);
t_ast_node	*p_build_separator(t_ast_node *left, t_ast_node *right, int type);
t_token		*copy_token_list(t_token **src);
/* 
 * Create function for all cases :::
 * -> REDIRECT IN
 *  -> REDIRECT OUT
 *  -> APPEND MODE
 *  -> PIPE
 *  -> SIMPLE COMMAND
 *  -> HEREDOC
 *  -> AND - OR - PIPE ---- IN THIS ORDER
 *  AFER BUILDING SINGLE NODES APPEND INTO MAIN 
 	STRUCT TO EXECUTE BASED ON PRIORITY ??
 */
// ITERATE THROUGH TOKEN LIST IF NO DELIMITER APPEND TO SIMPLE COMMAND
/////////////////////////////////////////////////////////
//////////////////// AST TEMPLATE ///////////////////////
/*
                 __ PIPE__
                     ___/              \____
                    /                       \
            COMMAND                    __ PIPE _
          /        \                  /         \
    ARGUMENTS   REDIRECTIONS	    CMD        _ CMD__
        |          |     |           |           /    \
       cat        <<     >       ARGUMENTS    ARGUMENTS	    REDIR
                   |     |         |   |      |   |   |        |
                 "..."  file      wc  -c      tr  -d " "       >
                                                               |
                                                             file2
*/

/**
 *
	<command line>	::= 	<job> ';' <command line>
						|	<job> ';'
						| 	<job> '&' <command line>
						|	<job> '&'
							<job>

	<job>			::=		<command> '|' <job>
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)

 *
 *
 *
**/

/* typedef union	ast_unions
{
	struct AST_SIMPLECMD
	{
		struct s_tree *right;
		struct s_tree *left;
	}	AST_SIMPLECMD;
	struct AST_REDIRECT_IN
	{
		AST_SIMPLECMD;
	}	AST_REDIRECT_IN;
	struct AST_REDIRECT_OUT 
	{
		AST_SIMPLECMD;
	}	AST_REDIRECT_IN;
	struct AST_APPEND 
	{
		struct s_tree *right; struct s_tree *left;
	}	AST_REDIRECT_IN;
	struct AST_HEREDOC 
	{
		struct s_tree *right; struct s_tree *left;
	}	AST_REDIRECT_IN;
}	u_ast_unions;
*/

/* BNF GRAMMAR FOR THE SHELL
<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z| 
	A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z 
<digit> ::= 0|1|2|3|4|5|6|7|8|9 <number> ::= <digit> | <number> <digit> 
<word> ::= <letter> | <word> <letter> | <word> '_' 
<word_list> ::= <word> | <word_list> <word> 
<assignment_word> ::= <word> '=' <word> 
<redirection> ::= '>' <word> | '<' <word> | <number> '>' 
<word> | <number> '<' <word> | '>>' <word> | 
<number> '>>' <word> | '<<' <word> | <number> '<<' <word> 
<simple_command_element> ::= <word> | <assignment_word> | <redirection> 
<redirection_list> ::= <redirection> | <redirection_list> <redirection> 
<simple_command> ::= <simple_command_element> 
| <simple_command> <simple_command_element> 
<command> ::= <simple_command> | <shell_command> 
| <shell_command> <redirection_list> 
*/

/*
typedef struct s_leaf
{
	char	**value;
	e_ast_type type;
}	t_leaf;
*/

#endif
