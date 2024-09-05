/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/05 12:32:52 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

t_ast_node	*p_build_tree(t_token *token, t_ast_utils *util)
{
	int			flag2;

	flag2 = 0;
	while (token)
	{
		flag2 = 0;
		if (token->type == TYPE_MINUS || token->type == TYPE_PLUS
			|| token->type == TYPE_EQUAL
			|| token->type == TOKEN || token->type == TYPE_LPAREN)
			p_parse_simple_command(&util, token);
		else if (token->type == TYPE_RSHIFT
			|| token->type == TYPE_LSHIFT || token->type == TYPE_APPEND
			|| token->type == TYPE_HEREDOC)
		{
			if (p_parse_redirect(&util, &token) == 0)
				flag2 = 1;
			else
				flag2 = 2;
		}
		else if (token->type == TYPE_PIPE)
			if (p_parse_pipeline(&util, &token))
				util->in_pipe = 1;
		if (token->type == TYPE_AND || token->type == TYPE_OR)
			if (p_parse_operators(&util, &token))
				break ;
		if (flag2 == 0)
			token = token->next;
		else if (flag2 == 2)
			token = token->next;
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	return (util->node);
}
