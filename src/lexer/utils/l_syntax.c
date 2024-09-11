/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_syntax.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:10:02 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 07:32:58 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

int	handle_logical_operators(t_token *temp, t_exec_utils *utils)
{
	if (!ft_strcmp(temp->next->value, "||")
		|| !ft_strcmp(temp->next->value, "&&"))
	{
		if (temp->type != TYPE_WORD && temp->next->next->type != TYPE_WORD)
		{
			print_syntax_error(temp,
				"minishell: syntax error near unexpected token", utils);
			return (0);
		}
	}
	return (1);
}

int	handle_semicolon_error(t_token *temp, t_exec_utils *utils)
{
	if (temp->type != TYPE_WORD)
	{
		print_syntax_error(temp,
			"minishell: syntax error near unexpected token", utils);
		return (0);
	}
	return (1);
}

int	valid_tok(t_token *temp, t_exec_utils **utils)
{
	if (temp->next->type == TYPE_PIPE || !ft_strcmp(temp->next->value, "||")
		|| !ft_strcmp(temp->next->value, "&&")
		|| !ft_strcmp(temp->next->value, ">>")
		|| !ft_strcmp(temp->next->value, ">")
		|| !ft_strcmp(temp->next->value, "<")
		|| !ft_strcmp(temp->next->value, "<<"))
	{
		if (!temp->next->next)
		{
			print_syntax_error(temp,
				"minishell: syntax error near unexpected token", *utils);
			return (0);
		}
		if (temp->next->type == TYPE_PIPE)
		{
			if (!handle_pipe_error(temp, *utils))
				return (0);
		}
		else if (!handle_redirection_type(temp, *utils))
			return (0);
		else if (!handle_logical_operators(temp, *utils))
			return (0);
	}
	return (1);
}

int	validate_tokens(t_token *temp, t_exec_utils **utils)
{
	while (temp)
	{
		if (temp->type == TYPE_LPAREN)
		{
			if (!validate_parentheses(temp, *utils))
				return (0);
		}
		if (temp->next)
		{
			if (!ft_strcmp(temp->next->value, ";"))
			{
				if (!handle_semicolon_error(temp, *utils))
					return (0);
			}
			if (!valid_tok(temp, utils))
				return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	validate_lexer(t_lexer **lex, t_exec_utils **utils)
{
	t_token	*temp;

	temp = (*lex)->token_list;
	if (!ft_strcmp(temp->value, "|") || !ft_strcmp(temp->value, "||")
		|| !ft_strcmp(temp->value, "&&") || !ft_strcmp(temp->value, ">>")
		|| !ft_strcmp(temp->value, ">") || !ft_strcmp(temp->value, ";"))
	{
		print_syntax_error(temp,
			"minishell: syntax error near unexpected token", *utils);
		return (0);
	}
	if (!ft_strcmp(temp->value, "<") || !ft_strcmp(temp->value, "<<"))
	{
		if (!handle_redirection_error(temp, *utils))
			return (0);
	}
	return (validate_tokens(temp, utils));
}
