/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 12:09:49 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

static void	p_parse_one(t_ast_utils *util, t_token **token, int type)
{
	if (type == TYPE_MINUS || type == TYPE_PLUS
		|| type == TYPE_EQUAL
		|| type == TOKEN || type == TYPE_LPAREN)
		p_parse_simple_command(&util, (*token));
}

static void	p_parse_two(t_ast_utils *util, t_token **token, int type, int *flag)
{
	if (type == TYPE_RSHIFT || type == TYPE_LSHIFT
		|| type == TYPE_APPEND || type == TYPE_HEREDOC)
	{
		if (p_parse_redirect(&util, token) == 0)
			*flag = 1;
		else
			*flag = 2;
	}
	else if (type == TYPE_PIPE)
		if (p_parse_pipeline(&util, token))
			util->in_pipe = 1;
}

t_ast_node	*p_build_tree(t_token *token)
{
	t_ast_utils		*util;
	t_ast_node		*node;
	int				flag2;

	flag2 = 0;
	p_init_vars(&util);
	while (token)
	{
		flag2 = 0;
		p_parse_one(util, &token, token->type);
		p_parse_two(util, &token, token->type, &flag2);
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
	node = util->node;
	free(util);
	return (node);
}
