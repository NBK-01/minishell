/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/19 11:52:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"


t_ast_node	*p_build_tree(t_token *token)
{
	t_ast_utils	*util;

	p_init_vars(&util);
	while (token)
	{
		if (token->type == TOKEN || token->type == TYPE_LPAREN
			|| token->type == TYPE_RSHIFT || token->type == TYPE_RSHIFT)
		{
			if (p_parse_simple_command(&util, &token) == 1)
				break ;
		}
		if (token->type == TYPE_PIPE)
			if (p_parse_pipeline(&util, &token))
				util->in_pipe = 1;
		if (token->type == TYPE_AND || token->type == TYPE_OR)
			if (p_parse_operators(&util, &token))
				break ;
		token = token->next;
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	return (util->node);
}