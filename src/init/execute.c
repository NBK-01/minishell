/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:39:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/05 12:28:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

void	free_tree(t_ast_node *node)
{
	int	i = 0;
	if (!node)
		return ;
	if (node->args)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free(node);
}

int	init_execute(t_syntax_tree *tree, t_env **env, t_exec_utils **util)
{
	(*util)->env = (*env);
	if (!tree)
		return (0);
	if (!tree->branch)
		return (0);
	if (!tree->branch->args)
		return (0);
	if (tree->branch->args[0] && !ft_strcmp(tree->branch->args[0], "()"))
		e_traverse_tree(tree->branch->tree_link->branch, (*util), env);
	else
		e_traverse_tree(tree->branch, (*util), env);
	return (0);
}
