/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/26 12:47:24 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"


t_ast_node	*p_build_pipeline(t_token **token)
{
	t_ast_utils	*util;
	int		flag;
	int		flag2 = 0;

	flag = 0;
	p_init_vars(&util);
	while ((*token))
	{
		flag2 = 0;
		if ((*token)->type == TOKEN || (*token)->type == TYPE_LPAREN)
			p_parse_simple_command(&util, (*token));
		else if ((*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_LSHIFT
				|| (*token)->type == TYPE_APPEND || (*token)->type == TYPE_HEREDOC)
		{
			if (p_parse_redirect(&util, token) == 0)
				flag2 = 1;
			else
				flag2 = 2;
		}
		else if ((*token)->type == TYPE_PIPE)
			if (p_parse_pipeline(&util, token))
				flag = 1;
		if (flag2 == 0)
			(*token) = (*token)->next; 
		if ((*token) && ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR))
		{
			if (!flag)
				util->node = p_build_simple_command(util);
			return (util->node);
		}
		if (flag2 == 2)
			(*token) = NULL;
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	return (util->node);
}




