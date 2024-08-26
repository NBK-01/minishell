/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:20:50 by mhabbal           #+#    #+#             */
/*   Updated: 2024/08/26 16:20:50 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"

int	p_parse_redirect(t_ast_utils **util, t_token **token)
{
	if ((*token)->type == TYPE_RSHIFT || (*token)->type == TYPE_APPEND)
	{
		if ((*token)->type == TYPE_APPEND)
			(*util)->append = 1;
		if ((*token)->next && (*token)->next->type == TOKEN)
			(*util)->files[0] = ft_strdup((*token)->next->value);
		if ((*token)->next && (*token)->next->next)
			(*token) = (*token)->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	}
	else if ((*token)->type == TYPE_LSHIFT || (*token)->type == TYPE_HEREDOC)
	{
		if ((*token)->type == TYPE_HEREDOC)
			(*util)->here_doc = 1;
		if ((*token)->next && (*token)->next->type == TOKEN)
			(*util)->files[1] = ft_strdup((*token)->next->value);
		if ((*token)->next && (*token)->next->next)
			(*token) = (*token)->next->next;
		else
		{
			(*util)->node = p_build_simple_command((*util));
			return (1);
		}
	}
	return (0);
}

int	p_parse_simple_command(t_ast_utils **util, t_token *token)
{

	if (token->type == TYPE_LPAREN)
	{
		(*util)->sub = &token->sub_lexer;
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	}
	if (token->type == TOKEN)
		(*util)->args = p_create_cmd_args(token->value, (*util)->args);
	return (0);
}

int	p_parse_pipeline(t_ast_utils **util, t_token **token)
{
	if ((*token)->type == TYPE_PIPE)
	{
		(*util)->node = p_build_simple_command((*util));
		free((*util)->args);
		(*util)->args = NULL;
		(*util)->right = p_build_pipeline(&(*token)->next);
		(*util)->node = p_build_separator((*util)->node, (*util)->right, (*token)->type);
		return (1);
	}
	else
		return (0);
}

int	p_parse_operators(t_ast_utils **util, t_token **token)
{
	if ((*token)->type == TYPE_AND || (*token)->type == TYPE_OR)
	{
		if (!(*util)->in_pipe)
			(*util)->node = p_build_simple_command((*util));
		free((*util)->args);
		(*util)->args = NULL;
		(*util)->right = p_build_tree((*token)->next);
		(*util)->node = p_build_separator((*util)->node, (*util)->right, (*token)->type);
		return (1);
	}
	else
		return (0);

}
