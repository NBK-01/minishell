/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:39:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 07:18:46 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

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
