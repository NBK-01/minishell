/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:00 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 19:33:23 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*l_vars_init(char *input, t_lexer *lex, t_token *token, t_env *env)
{
	lex->token_list = token;
	lex->token_list->sub_lexer = NULL;
	lex->util->i = 0;
	lex->util->j = 0;
	lex->util->input = input;
	lex->util->input_ptr = input;
	lex->util->expand = 1;
	lex->util->env = env;
	return (token);
}

void	init_token(t_token *token, int n, int id)
{
	token->value = malloc(sizeof(char) * (n + 1));
	token->value[0] = TYPE_NULL;
	token->type = TYPE_NULL;
	token->id = id + 1;
	token->next = NULL;
}

int	set_type(t_lexer **lex)
{
	int		type;

	(*lex)->util->c = *(*lex)->util->input_ptr;
	type = l_assign_type((*lex)->util->c);
	return (type);
}

int	init_lexer(char *input, t_lexer **lex, t_token **token, t_env *env)
{
	int		state;
	int		type;
	size_t	len;

	if (input)
		len = ft_strlen(input);
	state = STATE_ANY;
	(*token) = l_vars_init(input, (*lex), (*token), env);
	init_token((*token), len, 0);
	while (*(*lex)->util->input_ptr)
	{
		type = set_type(lex);
		if (l_tokenize((*lex), token, type, &state) == 1)
		{
			if ((*lex)->util->j > 0)
				(*token)->value[(*lex)->util->j] = '\0';
			(*lex)->util->rec_count -= 1;
			return (l_token_count((*lex), (*token), env));
		}
		(*lex)->util->i++;
		(*lex)->util->input_ptr++;
	}
	if ((*lex)->util->j > 0)
		(*token)->value[(*lex)->util->j] = '\0';
	(*token) = (*lex)->token_list;
	return (l_token_count((*lex), (*token), env));
}
