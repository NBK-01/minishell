/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:03:00 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 15:46:50 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	exec_pwd(char **args, t_exec_utils **util)
{
	char	*cwd;

	if (args[1] && ft_strchr(args[1], '-'))
	{
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(" :pwd: invalid option", 2);
		(*util)->code = 2;
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return ;
	}
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}
