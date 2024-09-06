/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_paren_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:42:25 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 14:04:38 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/lexer.h"

static void fill_paran(t_token *token_list, int id);

int count_paran(char *input, char paran)
{
    int counter;
    int i;
    int flag = 0;

    counter = 0;
    i = 0;
    while (input[i])
    {
        if (input[i] == '\"' || input[i] == '\'')
        {
            if (!flag)
                flag = 1;
            else
                flag = 0;
        }
        if (input[i] == paran)
        {
            if (!flag)
                counter++;
        }
        i++;
    }
    return (counter);
}

void l_recursive_fill(t_lexer *lex, int id)
{
    if (!lex)
        return;
    if (lex->token_list)
        fill_paran(lex->token_list, id);
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
        if (token_list->sub_lexer)
            l_recursive_fill(token_list->sub_lexer, 0);
        token_list = token_list->next;
    }
}

int close_values(char *input, t_lexer **lexer, t_exec_utils **utils)
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
        ft_putendl_fd("Syntax Error", 2);
        (*utils)->code = 2;
        return (0);
    }
    return (1);
}
