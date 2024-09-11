/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_build_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:52:20 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 07:34:49 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

static void	first_part(t_lexer **lex, t_ast_utils **util, t_token **tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_MINUS || token->type == TYPE_PLUS
		|| token->type == TYPE_EQUAL
		|| token->type == TOKEN || token->type == TYPE_LPAREN)
		p_parse_simple_command(util, lex, (*tok));
	else if (token->type == TYPE_RSHIFT || token->type == TYPE_LSHIFT
		|| token->type == TYPE_APPEND || token->type == TYPE_HEREDOC)
	{
		if (p_parse_redirect(util, lex, tok) == 0)
			(*util)->flag2 = (*util)->flag2 + 1;
		else
			(*util)->flag2 = (*util)->flag2 + 2;
	}
	else if (token->type == TYPE_PIPE)
		if (p_parse_pipeline(util, lex, (*tok)))
			(*util)->flag1 = 1;
}

static t_ast_node	*second_part(t_lexer **lex, t_ast_utils **util,
			t_token **tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token)
	{
		if ((*util)->flag2 == 0)
		{
			(*tok) = (*tok)->next;
			(*lex)->token_list = (*lex)->token_list->next;
		}
		if (token && (token->type == TYPE_AND || token->type == TYPE_OR))
		{
			if (!(*util)->flag1)
				(*util)->node = p_build_simple_command((*util));
			return ((*util)->node);
		}
		if ((*util)->flag2 == 2)
		{
			(*tok) = NULL;
			(*lex)->token_list = NULL;
		}
	}
	return (NULL);
}

t_ast_node	*p_build_pipeline(t_lexer **lex, t_token *tok)
{
	t_ast_utils	*util;
	t_ast_node	*node;

	p_init_vars(&util);
	util->flag1 = 0;
	util->flag2 = 0;
	(*lex)->token_list = (*lex)->token_list->next;
	tok = tok->next;
	while ((*lex)->token_list)
	{
		util->flag2 = 0;
		first_part(lex, &util, &tok);
		if (second_part(lex, &util, &tok))
			return (util->node);
	}
	if (!(util->node))
		util->node = p_build_simple_command(util);
	node = util->node;
	free(util->args);
	free(util);
	return (node);
}
