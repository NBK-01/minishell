/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:41 by nbk               #+#    #+#             */
/*   Updated: 2024/09/03 15:12:50 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	count_dash(char *args)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (args[i])
	{
		if (args[i] == '-')
			counter++;
		else if (args[i] != 'n')
			return (0);
		i++;
	}
	if (counter > 1)
		return (0);
	else
		return (1);
}

void	opt_helper(t_ast_node *node)
{
	int	i;

	i = 1;
	while (node->args[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(node->args[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}

int	exec_echo_opt(t_ast_node *node)
{
	int	i;

	if (!ft_strncmp("-n", node->args[1], 2))
	{
		if (count_dash(node->args[1]))
		{
			i = 2;
			while (node->args[i])
			{
				if (i > 2)
					ft_putstr_fd(" ", 1);
				ft_putstr_fd(node->args[i], 1);
				i++;
			}
		}
		else
			opt_helper(node);
		return (1);
	}
	return (0);
}

void	exec_echo(t_ast_node *node, t_exec_utils **util)
{
	int	i;

	if (!node->args[1])
	{
		ft_putstr_fd("\n", 1);
		(*util)->code = 0;
		exit (0);
	}
	if (exec_echo_opt(node))
		return ;
	i = 1;
	while (node->args[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(node->args[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}
