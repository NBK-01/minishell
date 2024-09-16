/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:37:03 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 11:50:49 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"
#include "../../../../includes/lexer.h"
#include <fcntl.h>
#include <errno.h>

int	p_parse_in(t_ast_utils **util, t_lexer **lex, t_token **tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	parse_heredoc(token, util);
	if (token->next && token->next->type == TOKEN)
	{
		(*util)->in = ft_strdup(token->next->value);
		if (!(*util)->here_doc)
			redirect_access_in(util);
	}
	if (token->next && token->next->next)
	{
		(*tok) = (*tok)->next->next;
		(*lex)->token_list = (*lex)->token_list->next->next;
	}
	else
	{
		(*util)->node = p_build_simple_command((*util));
		return (1);
	}
	return (0);
}

int	p_parse_redirect(t_ast_utils **util, t_lexer **lex, t_token **tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_RSHIFT || token->type == TYPE_APPEND)
	{
		if (token->type == TYPE_APPEND)
			(*util)->append = 1;
		if (token->next && token->next->type == TOKEN)
		{
			(*util)->out = ft_strdup(token->next->value);
			redirect_access(util);
		}
		if (token->next && token->next->next)
			skip_token(tok, lex);
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	}
	else if (token->type == TYPE_LSHIFT || token->type == TYPE_HEREDOC)
		if (p_parse_in(util, lex, tok))
			return (1);
	return (0);
}

int	p_parse_simple_command(t_ast_utils **util, t_lexer **lex, t_token *tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_LPAREN)
	{
		(*util)->sub = &tok->sub_lexer;
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	}
	if (token->type == TOKEN || token->type == TYPE_EQUAL)
	{
		if (!ft_strncmp(token->value, "-n", 2))
		{
			if (count_dash(token->value))
				(*util)->echo_flag = 1;
		}
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	}
	return (0);
}

int	p_parse_pipeline(t_ast_utils **util, t_lexer **lex, t_token *tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_PIPE)
	{
		(*util)->node = p_build_simple_command((*util));
		free((*util)->args);
		(*util)->args = NULL;
		(*util)->right = p_build_pipeline(lex, tok);
		(*util)->node = p_build_separator((*util)->node,
				(*util)->right, TYPE_PIPE);
		return (1);
	}
	else
		return (0);
}

int	p_parse_operators(t_ast_utils **util, t_lexer **lex, t_token **tok)
{
	t_token	*token;

	token = (*lex)->token_list;
	if (token->type == TYPE_AND || token->type == TYPE_OR)
	{
		if (!(*util)->in_pipe)
			(*util)->node = p_build_simple_command((*util));
		free((*util)->args);
		(*util)->args = NULL;
		(*lex)->token_list = (*lex)->token_list->next;
		(*tok) = (*tok)->next;
		(*util)->right = p_build_tree(lex, (*tok));
		(*util)->node = p_build_separator((*util)->node,
				(*util)->right, token->type);
		return (1);
	}
	else
		return (0);
}
