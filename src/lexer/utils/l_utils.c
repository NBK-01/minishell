/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:38 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:26:32 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

void	set_heredoc_eof(t_token **token)
{
	if ((*token)->type == TYPE_HEREDOC
		&& ((*token)->next->value[0] == '\''
			|| (*token)->next->value[0] == '\"'))
	{
		(*token)->expand = -10;
		(*token)->next->expand = 0;
	}
}

int	l_token_count(t_lexer *lex, t_token *token, t_env *env)
{
	int		hits;
	char	**matches;
	char	*expanded;

	token = lex->token_list;
	while (token)
	{
		set_heredoc_eof(&token);
		if (token->type == TOKEN)
		{
			matches = l_glob(token->value, &hits);
			if (hits > 0)
				l_handler_wildcards(token, hits, matches);
			else
				token->value = l_remove_quotes(token);
			expanded = expand_variables(token->value, token->expand, env);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
			}
		}
		token = token->next;
	}
	return (0);
}

void	l_tokenize_words(t_lexer *lex, t_token *token, int type)
{
	if (type == TYPE_ESC)
	{
		token->value[lex->util->j++] = ++(*lex->util->input_ptr);
		token->type = TOKEN;
	}
	else if (type == TYPE_WORD)
	{
		token->value[lex->util->j++] = lex->util->c;
		token->type = TOKEN;
	}
}

void	l_tokenize_next(t_lexer *lex, t_token **token, int type, int len)
{
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	if (type != TYPE_SPACE)
	{
		(*token)->value[0] = type;
		(*token)->value[1] = '\0';
		(*token)->type = type;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
	}
}
