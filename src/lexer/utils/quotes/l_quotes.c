/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                               +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:34 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/07 09:07:35 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"

static void	clean_input(char *input, char *res);

void	l_state_handler_quote_in(t_lexer *lex, t_token **token,
			int type, int *state)
{
	if (type == TYPE_QUOTE)
	{
		(*state) = IN_QUOTES;
		(*token)->expand = 0;
		(*token)->value[lex->util->j++] = TYPE_QUOTE;
		(*token)->type = TOKEN;
	}
	if (type == TYPE_DQUOTE)
	{
		(*state) = IN_DQUOTES;
		(*token)->expand = 1;
		(*token)->value[lex->util->j++] = TYPE_DQUOTE;
		(*token)->type = TOKEN;
	}
}

void	l_state_handler_quote_exit(t_lexer *lex, t_token **token,
				int type, int *state)
{
	if ((*state) == IN_DQUOTES)
	{
		(*token)->value[lex->util->j++] = lex->util->c;
		if (type == TYPE_DQUOTE)
			(*state) = STATE_ANY;
	}
	else if ((*state) == IN_QUOTES)
	{
		(*token)->value[lex->util->j++] = lex->util->c;
		if (type == TYPE_QUOTE)
			(*state) = STATE_ANY;
	}
}

char	*l_remove_quotes(t_token *token)
{
	char	*clean;

	clean = ft_calloc(1, ft_strlen(token->value) + 1);
	clean_input(token->value, clean);
	free(token->value);
	return (clean);
}

int	clean_input_helper(int len, char *input, char *res)
{
	if (len <= 1)
	{
		ft_strcpy(res, input);
		return (1);
	}
	return (0);
}

static void	clean_input(char *input, char *res)
{
	char	end_literal;
	size_t	len;
	size_t	i;
	int		j;
	char	c;

	len = ft_strlen(input);
	end_literal = 0;
	j = 0;
	i = 0;
	if (clean_input_helper(len, input, res))
		return ;
	while (i < len)
	{
		c = input[i];
		if ((c == 34 || c == 39) && end_literal == 0)
			end_literal = c;
		else if (end_literal == c)
			end_literal = 0;
		else
			res[j++] = c;
		i++;
	}
	res[j] = '\0';
}
