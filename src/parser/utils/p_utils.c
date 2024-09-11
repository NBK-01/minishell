/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:56 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 14:55:14 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/ast.h"
#include "../../../includes/token.h"
#include <fcntl.h>
#include <errno.h>

void	redirect_access_in(t_ast_utils **util)
{
	int	fd;

	fd = open((*util)->in, O_RDONLY);
	if (fd < 0)
	{
		if ((*util)->exit == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror((*util)->in);
		}
		(*util)->exit = 1;
		close(fd);
	}
	close(fd);
}

void	redirect_access(t_ast_utils **util)
{
	int	fd;

	if ((*util)->exit == 0)
		fd = open((*util)->out, O_WRONLY | O_CREAT, 0644);
	else
		fd = open((*util)->out, O_WRONLY);
	if (fd < 0 && errno == 13)
	{
		if ((*util)->exit == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror((*util)->out);
		}
		(*util)->exit = 1;
		close(fd);
	}
	close(fd);
}

char	*p_create_cmd_args(char *value, char *args)
{
	char	*whitespace;
	char	*temp;

	if (!args)
		args = ft_strdup(value);
	else
	{
		whitespace = ft_strjoin(args, " ");
		temp = ft_strjoin(whitespace, value);
		free(whitespace);
		free(args);
		args = temp;
	}
	return (args);
}

t_ast_utils	*p_init_vars(t_ast_utils **util)
{
	(*util) = ft_calloc(1, sizeof(t_ast_utils));
	(*util)->in = NULL;
	(*util)->out = NULL;
	(*util)->in_pipe = 0;
	(*util)->exit = 0;
	(*util)->sub = NULL;
	(*util)->node = NULL;
	(*util)->right = NULL;
	(*util)->echo_flag = 0;
	return ((*util));
}

void	p_expand_tree(t_ast_node *node)
{
	if (!node)
		return ;
	else if (node->args && node->args[0] && !(ft_strcmp(node->args[0], "()")))
	{
		node->tree_link = ft_calloc(1, sizeof(t_syntax_tree));
		init_parser(node->lexer, &node->tree_link);
		if (!node->tree_link->branch->out)
			if (node->out)
				node->tree_link->branch->out = ft_strdup(node->out);
		if (!node->tree_link->branch->in)
		{
			if (node->in)
				node->tree_link->branch->in = ft_strdup(node->in);
			node->tree_link->branch->here_doc = node->here_doc;
		}
	}
	p_expand_tree(node->left);
	p_expand_tree(node->right);
}
