/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:12:41 by nbk               #+#    #+#             */
/*   Updated: 2024/09/16 12:11:16 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"

static void	init_vars(int *flag, int *i)
{
	*flag = 0;
	*i = 0;
}

int	check_char(char **args)
{
	int	i;
	int	j;
	int	flag;

	init_vars(&flag, &i);
	if (ft_strncmp(args[i], "-n", 2) != 0)
		return (0);
	while (args[++i])
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][0] == '-')
			{
				if (args[i][j] != 'n')
					return (flag);
				else
					j++;
			}
			else
				return (flag);
		}
		flag = 1;
	}
	return (1);
}

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

int	exec_echo_opt(t_ast_node *node)
{
	int	i;
	int	j;

	i = 1;
	if (check_char(node->args))
	{
		while (node->args[i] && count_dash(node->args[i]))
			i++;
		if (!node->args[i])
			return (3);
		j = i;
		while (node->args[i])
		{
			if (i > j)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(node->args[i], 1);
			i++;
		}
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
	else if (exec_echo_opt(node) == 3)
	{
		(*util)->code = 0;
		exit (0);
	}
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
