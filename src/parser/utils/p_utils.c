#include "../../../includes/minishell.h"
#include "../../../includes/ast.h"
#include "../../../includes/token.h"

char	*p_create_cmd_args(char *value, char *args)
{
	char	*whitespace;
	char	*temp;

	// printf("%s\n", value);
	if (!args)
		args = ft_strdup(value);
	else
	{
		whitespace = ft_strjoin(args, " ");
		temp = ft_strjoin(whitespace, value);
		free(whitespace);
		free(args);
		args = temp;
	}
	return (args);
}

t_ast_utils	*p_init_vars(t_ast_utils **util)
{
	(*util) = ft_calloc(1, sizeof(t_ast_utils));
	(*util)->files = (char **)ft_calloc(2, sizeof(char *));
	(*util)->in_pipe = 0;
	(*util)->sub = NULL;
	(*util)->node = NULL;
	(*util)->right = NULL;
	(*util)->echo_flag = 0;
	return ((*util));
}

void	p_expand_tree(t_ast_node *node)
{
	if (!node)
		return ;
	else if (node->args && node->args[0] && !(ft_strcmp(node->args[0], "()")))
	{
		node->tree_link = ft_calloc(1, sizeof(t_syntax_tree));
		init_parser(node->lexer, &node->tree_link);
	}
	if (node->left)
		p_expand_tree(node->left);
	if (node->right)
		p_expand_tree(node->right);
}
