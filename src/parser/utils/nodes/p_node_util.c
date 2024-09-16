/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_node_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:51:13 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:40:00 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/ast.h"
#include "../../../../includes/token.h"
#include "../../../../includes/lexer.h"
#include <fcntl.h>
#include <errno.h>

void	parse_heredoc(t_token *token, t_ast_utils **util)
{
	if (token->type == TYPE_HEREDOC)
	{
		if (token->expand == -10)
			(*util)->here_doc = 2;
		else
			(*util)->here_doc = 1;
	}
}
