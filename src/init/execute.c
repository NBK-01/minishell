/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:19:39 by mhabbal           #+#    #+#             */
/*   Updated: 2024/08/26 16:19:55 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	init_execute(t_syntax_tree *tree, t_env *env, t_exec_utils **util)
{
	(*util)->env = env;
	if (!tree)
		return (0);
	if (!tree->branch)
		return (0);
	if (!tree->branch->args)
		return (0);
	if (!ft_strcmp(tree->branch->args[0], "()"))
		e_traverse_tree(tree->branch->tree_link->branch, (*util));
	else
		e_traverse_tree(tree->branch, (*util));
	return (0);
}
