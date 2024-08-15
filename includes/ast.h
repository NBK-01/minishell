#ifndef AST_H
# define AST_H
# include "./minishell.h"
# include "./token.h"

struct s_synatx_tree;


#define ASSIGN(x) ((x) == TYPE_PIPE ? "|"  : \
                          (x) == TYPE_AND ? "&&"   : \
                          (x) == TYPE_OR ? "||"   : \
                                     "")
#define ASSIGN_TYPE(type) (type == TYPE_PIPE) ? AST_PIPE: (type == TYPE_AND) ? AST_AND:  (type == TYPE_OR) ? AST_OR: 0

// Follow BNF Format
typedef enum node_type
{
	AST_PIPE,
	AST_REDIRECT_FROM,
	AST_REDIRECT_TO,
	AST_COMMAND,
	AST_AND,
	AST_OR,
	AST_FILE,
}	e_node_type;

typedef struct s_ast_node
{
	char	**args;			// 2d array for exec?? maybe single ptr -- check again
	char	*in;
	char	*out;
	struct s_ast_node	*left;  // Normal binary tree
	struct s_ast_node	*right; // Normal binary tree node
	struct s_syntax_tree	*tree_link;
	//t_lexer		**lexer;
	e_node_type	type; // Type of node -> if pipe takes left and right 
	int	id; // ?????? to check for parens??
	t_token	*sub;
}	t_ast_node;

typedef struct s_syntax_tree
{
	struct s_ast_node	*branch;
}	t_syntax_tree;

void	init_parser(t_lexer **lexer, t_syntax_tree **tree);
t_ast_node	*p_build_tree(t_token *token);
char	*p_create_cmd_args(char *value, char *args);
/* 
 * Create function for all cases :::
 * -> REDIRECT IN
 *  -> REDIRECT OUT
 *  -> APPEND MODE
 *  -> PIPE
 *  -> SIMPLE COMMAND
 *  -> HEREDOC
 *  -> AND - OR - PIPE ---- IN THIS ORDER
 *  AFER BUILDING SINGLE NODES APPEND INTO MAIN STRUCT TO EXECUTE BASED ON PRIORITY ??
 */
t_ast_node	*p_build_simple_command(char *cmd, char *in, char *out, int id);
t_ast_node	*p_build_pipe(t_ast_node *left, t_ast_node *right, int id);
t_ast_node	*p_build_redirect_to(t_ast_node *left, char *outfile);
t_ast_node	*p_build_redirect_from(t_ast_node *left, char *infile);
t_ast_node	*find_right(t_lexer **lex);
// ITERATE THROUGH TOKEN LIST IF NO DELIMITER APPEND TO SIMPLE COMMAND
/////////////////////////////////////////////////////////////////////////////////////////
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

// DO MORE RESEARCH ON HOW UNIONS WORK IN C AND HOW WE CAN UTILIZE IT WHILE PARSING


/* BNF GRAMMAR FOR THE SHELL
<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z| 
	A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z 
<digit> ::= 0|1|2|3|4|5|6|7|8|9 <number> ::= <digit> | <number> <digit> 
<word> ::= <letter> | <word> <letter> | <word> '_' 
<word_list> ::= <word> | <word_list> <word> 
<assignment_word> ::= <word> '=' <word> 
<redirection> ::= '>' <word> | '<' <word> | <number> '>' <word> | <number> '<' <word> | '>>' <word> | <number> '>>' <word> | '<<' <word> | <number> '<<' <word> 
<simple_command_element> ::= <word> | <assignment_word> | <redirection> 
<redirection_list> ::= <redirection> | <redirection_list> <redirection> 
<simple_command> ::= <simple_command_element> | <simple_command> <simple_command_element> 
<command> ::= <simple_command> | <shell_command> | <shell_command> <redirection_list> 
*/

/*
typedef struct s_leaf
{
	char	**value;
	e_ast_type type;
}	t_leaf;
*/


#endif
