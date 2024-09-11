/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_syntax_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:10:07 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 07:21:52 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

void	print_syntax_error(t_token *token, char *prefix, t_exec_utils *utils)
{
	ft_putstr_fd(prefix, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(token->value, 2);
	ft_putendl_fd("\'", 2);
	utils->code = 2;
}

int	handle_redirection_error(t_token *temp, t_exec_utils *utils)
{
	if (!temp->next || temp->next->type != TYPE_WORD)
	{
		print_syntax_error(temp,
			"minishell: syntax error near unexpected token", utils);
		return (0);
	}
	return (1);
}

int	validate_parentheses(t_token *temp, t_exec_utils *utils)
{
	if (!temp->sub_lexer || !temp->sub_lexer->token_list->value[0])
	{
		print_syntax_error(temp,
			"minishell: syntax error near unexpected token", utils);
		return (0);
	}
	if (!validate_lexer(&temp->sub_lexer, &utils))
		return (0);
	return (1);
}

int	handle_pipe_error(t_token *temp, t_exec_utils *utils)
{
	if ((temp->type != TYPE_LPAREN && temp->type != TYPE_WORD)
		&& (temp->next->next->type != TYPE_LSHIFT
			&& temp->next->next->type != TYPE_RSHIFT
			&& temp->next->next->type != TYPE_WORD
			&& temp->next->next->type != TYPE_LPAREN
			&& temp->next->next->type != TYPE_HEREDOC
			&& temp->next->next->type != TYPE_APPEND))
	{
		print_syntax_error(temp,
			"minishell: syntax error near unexpected token", utils);
		return (0);
	}
	return (1);
}

int	handle_redirection_type(t_token *temp, t_exec_utils *utils)
{
	if (!ft_strcmp(temp->next->value, ">>")
		|| !ft_strcmp(temp->next->value, ">")
		|| !ft_strcmp(temp->next->value, "<")
		|| !ft_strcmp(temp->next->value, "<<"))
	{
		if ((temp->type != TYPE_WORD || temp->type != TYPE_PIPE)
			&& temp->next->next->type != TYPE_WORD)
		{
			print_syntax_error(temp,
				"minishell: syntax error near unexpected token", utils);
			return (0);
		}
	}
	return (1);
}
