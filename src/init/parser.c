/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 07:13:17 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"
#include "../../includes/minishell.h"

void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	(*tree)->branch = p_build_tree(lex, (*lex)->token_list);
	if ((*tree)->branch->args)
		p_expand_tree((*tree)->branch);
}
