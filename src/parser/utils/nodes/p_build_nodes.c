/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:22:28 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 15:01:22 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"

void	build_simple_command_vars(t_ast_node **node, t_ast_utils **util)
{
	t_ast_utils	*temp;

	temp = (*util);
	(*node)->type = AST_COMMAND;
	(*node)->in = temp->in;
	(*node)->out = temp->out;
	(*node)->append = temp->append;
	(*node)->exit = temp->exit;
	(*node)->here_doc = temp->here_doc;
	if (temp->sub)
		(*node)->lexer = temp->sub;
	(*node)->right = NULL;
	(*node)->left = NULL;
}

t_ast_node	*p_build_simple_command(t_ast_utils *util)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (util->args)
	{
		if (!ft_strcmp(util->args, "echo") && util->echo_flag == 0)
		{
			node->args = malloc(3 * sizeof(char *));
			node->args[0] = ft_strdup("echo");
			node->args[1] = ft_substr(util->args, 5, ft_strlen(util->args));
			node->args[2] = NULL;
		}
		else
			node->args = ft_split(util->args, ' ');
		build_simple_command_vars(&node, &util);
	}
	return (node);
}

static char	*assign_val(int type)
{
	if (type == TYPE_PIPE)
		return ("|");
	if (type == TYPE_AND)
		return ("&&");
	if (type == TYPE_OR)
		return ("||");
	return ("");
}

static t_node_type	assign_type(int type)
{
	if (type == TYPE_PIPE)
		return (AST_PIPE);
	if (type == TYPE_AND)
		return (AST_AND);
	if (type == TYPE_OR)
		return (AST_OR);
	return (AST_COMMAND);
}

t_ast_node	*p_build_separator(t_ast_node *left, t_ast_node *right, int type)
{
	t_ast_node	*node;
	char		*delim;

	node = ft_calloc(1, sizeof(t_ast_node));
	node->left = left;
	node->right = right;
	node->type = assign_type(type);
	delim = assign_val(type);
	node->args = ft_split(delim, ' ');
	return (node);
}
