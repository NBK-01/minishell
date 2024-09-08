/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 12:14:05 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

static void first_part(t_token **token, t_ast_utils **util, int *flag2, int *flag)
{
	if ((*token)->type == TYPE_MINUS || (*token)->type == TYPE_PLUS || (*token)->type == TYPE_EQUAL || (*token)->type == TOKEN || (*token)->type == TYPE_LPAREN)
		p_parse_simple_command(util, (*token));
	else if ((*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_LSHIFT || (*token)->type == TYPE_APPEND || (*token)->type == TYPE_HEREDOC)
	{
		if (p_parse_redirect(util, token) == 0)
			*flag2 = *flag2 + 1;
		else
			*flag2 = *flag2 + 2;
	}
	else if ((*token)->type == TYPE_PIPE)
		if (p_parse_pipeline(util, token))
			*flag = 1;
}

static t_ast_node *second_part(t_token **token, t_ast_utils **util, int *flag2,
							   int *flag)
{
	if (*flag2 == 0)
		(*token) = (*token)->next;
	if ((*token) && ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR))
	{
		if (!*flag)
			(*util)->node = p_build_simple_command((*util));
		return ((*util)->node);
	}
	if (*flag2 == 2)
		(*token) = NULL;
	return (NULL);
}

t_ast_node *p_build_pipeline(t_token **token)
{
	t_ast_utils *util;
	t_ast_node *node;
	int flag;
	int flag2;

	flag = 0;
	flag2 = 0;
	p_init_vars(&util);
	while ((*token))
	{
		flag2 = 0;
		first_part(token, &util, &flag2, &flag);
		if (second_part(token, &util, &flag2, &flag))
			return (util->node);
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	node = util->node;
	free(util);
	return (node);
}
