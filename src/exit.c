/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:29:51 by nbk               #+#    #+#             */
/*   Updated: 2024/09/03 15:37:41 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/execute.h"

void	exit_operations(char **args, t_exec_utils *util)
{
	int		nbr;
	char	*delim;

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

void	exit_args(char **args)
{
	int	nbr;
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (ft_isdigit(args[1][i]))
			i++;
		else
		{
			ft_putendl_fd("exit", 0);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
	}
	nbr = ft_atoi(args[1]);
	if (nbr > 256)
		nbr -= 256;
	ft_putendl_fd("exit", 0);
	exit(nbr);
}

int	handle_exit(t_exec_utils *util, char **args)
{
	if (!args[1])
	{
		ft_putendl_fd("exit", 0);
		exit(util->code);
	}
	if (args[2])
	{
		ft_putendl_fd("exit", 0);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putendl_fd("too many arguments", 2);
		exit(1);
	}
	else if (args[1])
	{
		exit_operations(args, util);
		exit_args(args);
	}
	return (1);
}
