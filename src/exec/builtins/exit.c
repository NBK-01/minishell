/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:29:51 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 14:06:49 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"
#include <limits.h>

void	exit_operations(char **args, t_exec_utils *util, t_ast_node *node)
{
	char	*delim;
	int		nbr;

	(void)node;
	delim = ft_strchr(args[1], '+');
	if (delim)
	{
		nbr = ft_atoi(delim + 1);
		util->code += nbr;
		exit(util->code);
	}
	else if (!delim)
	{
		delim = ft_strchr(args[1], '-');
		if (delim)
		{
			nbr = ft_atoi(delim + 1);
			util->code = 256 - nbr;
			ft_putendl_fd("exit", 0);
			exit(util->code);
		}
	}
}

static	void	exit_message(char **args, int flag)
{
	if (flag)
	{
		ft_putendl_fd("exit", 0);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
}

void	exit_args(char **args)
{
	__int128	nbr;
	int			flag;
	int			i;

	i = 0;
	flag = 0;
	nbr = ft_atoll(args[1]);
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]))
			i++;
		else
		{
			flag = 1;
			break ;
		}
	}
	if (ft_atoll(args[1]) > LLONG_MAX || (ft_atoll(args[1]) < LLONG_MIN))
		flag = 1;
	exit_message(args, flag);
	nbr = ft_atoll(args[1]);
	if (nbr > 256)
		nbr -= 256;
	ft_putendl_fd("exit", 0);
	exit(nbr);
}

int	handle_exit(t_exec_utils *util, t_ast_node *node)
{
	char	**args;

	args = NULL;
	if (node && node->args)
		args = node->args;
	if (args && !args[1])
	{
		ft_putendl_fd("exit", 0);
		free_ast(node);
		exit(util->code);
	}
	if (args && args[2])
	{
		ft_putendl_fd("exit", 0);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		free_ast(node);
		exit(2);
	}
	else if (args && args[1])
	{
		exit_operations(args, util, node);
		exit_args(args);
	}
	return (1);
}
