/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:55 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 07:33:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./minishell.h"
# include "./token.h"
# include "./execute.h"

typedef struct s_node
{
	char			*data;
	struct s_node	*next;
}	t_node;

typedef struct s_expand
{
	t_node		*list_head;
	t_node		*last_node;
	char		*start;
	char		*pid;
	char		*exit_code;
	char		*var_start;
	size_t		len;
	char		*var_name;
	char		*env_value;
	char		*text_start;
	size_t		text_len;
	char		*text;
	size_t		total_len;
	t_node		*curr;
	char		*res;
	char		*ptr;
	size_t		data_len;
}	t_expand;

int		handle_redirection_type(t_token *temp, t_exec_utils *utils);
int		handle_pipe_error(t_token *temp, t_exec_utils *utils);
int		validate_parentheses(t_token *temp, t_exec_utils *utils);
int		validate_tokens(t_token *temp, t_exec_utils **utils);
int		valid_tok(t_token *temp, t_exec_utils **utils);
int		handle_semicolon_error(t_token *temp, t_exec_utils *utils);
int		handle_logical_operators(t_token *temp, t_exec_utils *utils);
void	print_syntax_error(t_token *token, char *prefix, t_exec_utils *utils);
int		handle_redirection_error(t_token *temp, t_exec_utils *utils);
int		validate_parentheses(t_token *temp, t_exec_utils *utils);
t_node	*append_node(t_node *head, char *data);
void	free_list(t_node *head);
void	expand_helper(t_expand *ex, t_env *env);
char	*get_env_value(const char *key, t_env *env);
void	free_ex(t_expand *ex);
int		validate_lexer(t_lexer **lex, t_exec_utils **utils);
// char	*l_expand(char *value, t_lex_utils *util, t_env *env);
char	*expand_variables(char *value, int exp, t_env *env);
/*/////////////////////////////////////////////////////////////
////////////		TYPES			    //////////
////////////////////////////////////////////////////////////*/
int		init_lexer(char *input, t_lexer **lex, t_token **token, t_env *env);
int		l_tokenize(t_lexer *lex, t_token **token, int type, int *state);
/*/////////////////////////////////////////////////////////////
////////////		QUOTES			    //////////
////////////////////////////////////////////////////////////*/
void	l_state_handler_quote_in(t_lexer *lex, t_token **token,
			int type, int *state);
void	l_state_handler_quote_exit(t_lexer *lex, t_token **token,
			int type, int *state);
char	*l_remove_quotes(t_token *token);

/*/////////////////////////////////////////////////////////////
////////////		OPERATORS		    //////////
////////////////////////////////////////////////////////////*/
void	l_tokenize_ampersand(t_lexer *lex, t_token **token,
			int *state, int type);
void	l_handler_ampersand(t_lexer *lex, t_token **token,
			int type, int *state);
void	l_tokenize_pipe(t_lexer *lex, t_token **token,
			int *state, int type);
void	l_tokenize_heredoc(t_lexer *lex, t_token **token,
			int *state, int type);
void	l_handler_heredoc(t_lexer *lex, t_token **token, int type, int *state);
void	l_handler_append(t_lexer *lex, t_token **token, int type, int *state);
void	l_handler_pipe(t_lexer *lex, t_token **token, int type, int *state);
void	l_tokenize_next(t_lexer *lex, t_token **token, int type, int len);
void	l_tokenize_words(t_lexer *lex, t_token *token, int type);
int		handle_paren(t_lexer **lex, t_token **token, int *state, int type);
t_token	*l_vars_init(char *input, t_lexer *lex, t_token *token);
/*/////////////////////////////////////////////////////////////
////////////		GLOBBING		    //////////
////////////////////////////////////////////////////////////*/
char	**l_glob(const char *pattern, int *hits);
int		l_glob_match(const char *pattern, const char *string);
void	l_handler_wildcards(t_token *token, int count, char **glob_list);
size_t	l_glob_count(const char *pattern);

/*/////////////////////////////////////////////////////////////
////////////		LEXER_UTILS		    //////////
////////////////////////////////////////////////////////////*/
int		close_values(char *input, t_lexer **lexer, t_exec_utils **util);

#endif
