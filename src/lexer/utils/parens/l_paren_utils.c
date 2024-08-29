/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_paren_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:42:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/12 14:16:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

int count_paran(char *input, char paran)
{
    int counter;
    int i;

    counter = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == paran)
            counter++;
        i++;
    }
    return (counter);
}

static void fill_paran(t_token *token_list, int id)
{
    (void)id;
    while (token_list)
    {
        if (ft_strcmp(token_list->value, "(") == 0)
        {
            free(token_list->value);
            token_list->value = ft_strjoin("(", ")");
        }
        token_list = token_list->next;
    }
}

void l_recursive_fill(t_lexer *lex, int id)
{
    t_lex_ll *child;

    if (!lex)
        return;
    if (lex->token_list)
        fill_paran(lex->token_list, id);
    if ((*lex->child))
    {
        child = (*lex->child);
        while (child)
        {
            if (child->lexer)
                l_recursive_fill(child->lexer, id + 1);
            child = child->next;
        }
    }
}

void special_fill(int num, t_lexer *lexer)
{
    int find;

    find = 0;
    while (find < num)
    {
        if (lexer->token_list)
        {
            if (ft_strcmp(lexer->token_list->value, "(") == 0)
                find++;
        }
        lexer = (*lexer->child)->lexer;
    }
    l_recursive_fill(lexer, 0);
}

void close_values(char *input, t_lexer **lexer, t_exec_utils **util)
{
    int l_paran_num;
    int r_paran_num;

    l_paran_num = count_paran(input, '(');
    r_paran_num = count_paran(input, ')');
    if (!(l_paran_num < r_paran_num))
    {
        l_recursive_fill((*lexer), 0);
    }
    else if (l_paran_num < r_paran_num)
	{
		ft_putendl_fd(" syntax error", 2);
		(*util)->code = 2;
	}
}
