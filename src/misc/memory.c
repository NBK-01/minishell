/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:33:24 by mhabbal           #+#    #+#             */
/*   Updated: 2024/09/10 14:21:51 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/token.h"
#include "../../includes/ast.h"

static void	free_tree(t_syntax_tree *tree)
{
	if (tree->branch)
		free_ast(tree->branch);
}

void	free_ast(t_ast_node *node)
{
	if (node)
	{
		if (node->tree_link)
		{
			free_tree(node->tree_link);
			free(node->tree_link);
		}
		if (node->left)
			free_ast(node->left);
		if (node->right)
			free_ast(node->right);
		if (node->args)
			free_split(node->args);
		if (node->in)
			free(node->in);
		if (node->out)
			free(node->out);
		if (node->lexer)
			if ((*node->lexer)->token_list)
				free_token_ll((*node->lexer)->token_list);
		free(node);
	}
}

void	free_lexer(t_lexer **lex)
{
	if (!lex && (*lex))
		return ;
	if ((*lex) && (*lex)->token_list)
		free_token_ll((*lex)->token_list);
	if ((*lex)->c_token)
		free_token_ll((*lex)->c_token);
	free((*lex)->util);
	free((*lex));
}

void	free_env_list(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = (*env);
	while (curr)
	{
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
}
