/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:56 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 19:15:35 by nkanaan          ###   ########.fr       */
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

	fd = open((*util)->files[1], O_RDONLY);
	if (fd < 0)
	{
		if ((*util)->exit == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror((*util)->files[1]);
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
		fd = open((*util)->files[0], O_WRONLY | O_CREAT, 0644);
	else
		fd = open((*util)->files[0], O_WRONLY);
	if (fd < 0 && errno == 13)
	{
		if ((*util)->exit == 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror((*util)->files[0]);
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
	(*util)->files = (char **)ft_calloc(2, sizeof(char *));
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
	}
	p_expand_tree(node->left);
	p_expand_tree(node->right);
}
