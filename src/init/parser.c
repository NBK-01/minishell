/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:45:23 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/05 12:43:19 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"



void	free_util(t_ast_utils *util)
{
	if (!util)
		return ;
	free(util->files[0]);
	free(util->files[1]);
	free(util->args);
	free(util);
}



void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	t_ast_utils	*util;

	p_init_vars(&util);
	(*tree)->branch = p_build_tree((*lex)->token_list, util);
	if ((*tree)->branch->args)
		p_expand_tree((*tree)->branch);
	free_util(util);
}
