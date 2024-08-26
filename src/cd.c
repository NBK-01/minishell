/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:50 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/26 16:55:05 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

char	*get_home_path(t_env **env)
{
	t_env	*temp;
	char	*home;

	temp = (*env);
	home = NULL;
	while (temp)
	{
		if(!ft_strcmp(temp->key, "HOME"))
		{
			home = ft_strdup(temp->value);
			break;
		}
		temp = temp->next;
	}
	return (home);
}

void	change_dir(t_exec_utils *util, char **args) 
{
	char	*home;
	char 	*path;

	home = get_home_path(&util->env);
	if (args[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			util->code = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;	
		}
		util->code = 0;
		return ;
	}
	path = ft_strdup(args[1]);
	if (path)
	{
		if (path[0] == '~')
			path = ft_strjoin(home, ft_substr(path, 1, ft_strlen(path)- 1));
		if (chdir(path) != 0)
		{
			util->code = 127;	
			perror("cd");
			return ;
		}
		util->code = 0;
	}
}
