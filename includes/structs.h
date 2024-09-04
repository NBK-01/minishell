#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

struct s_lex_ll;
struct s_lexer;
struct s_token;
struct s_lex_util;

typedef struct s_syntax_tree
{
	struct s_ast_node	*branch;
}	t_syntax_tree;

typedef struct	s_env
{
	char	**og;
	char	*key;
	char	*value;
	struct s_env	*next;
	int		code;
	int	hidden;
}	t_env;

typedef struct s_exec_utils
{
	int	code;
	int	exit_code;
	int	code_count;
	t_env	*env;
}   t_exec_utils;

typedef struct s_lex_ll
{
	int	id;
	struct s_lex_ll	*next;
	struct s_lexer	*lexer;
}	t_lex_ll;

typedef struct s_token
{
	char	*value;
	int	type;
	struct s_lexer *sub_lexer;
	struct s_token *next;
	int  id;
}	t_token;

typedef struct	s_lex_utils
{
	char	c;
	int	i;
	int	j;
	char	*input;
	char	*input_ptr;
	int	rec_count;
	int	clock;
	int	expand;
	t_env	*env;
}	t_lex_utils;

typedef struct s_lexer
{
	t_token	*token_list;
	t_lex_utils	*util;
	t_lex_ll	**child;
	int		count;
}	t_lexer;


#endif
