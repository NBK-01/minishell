/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:37:49 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 15:54:48 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

char	*get_cd_path(t_env **env, char *path)
{
	t_env	*temp;
	char	*home;

	temp = (*env);
	home = NULL;
	while (temp)
	{
		if (!ft_strcmp(temp->key, path))
		{
			home = temp->value;
			break ;
		}
		temp = temp->next;
	}
	return (home);
}

int	home_cd(t_exec_utils *util, char **args)
{
	char	*home;

	home = get_cd_path(&util->env, "HOME");
	if (args[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			util->code = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		util->code = 0;
		return (1);
	}
	return (0);
}

int	path_cd(t_exec_utils *util, char **args)
{
	char	*path;
	char	*home;

	home = get_cd_path(&util->env, "HOME");
	path = ft_strdup(args[1]);
	if (path)
	{
		if (path[0] == '~')
			path = ft_strjoin(home, ft_substr(path, 1, ft_strlen(path) - 1));
		if (chdir(path) != 0)
		{
			util->code = 1;
			perror("cd");
			free(path);
			return (1);
		}
		util->code = 0;
	}
	if (path)
		free(path);
	return (0);
}

int	oldpwd_cd(t_exec_utils *util, char **args)
{
	char	*oldpwd;
	char	*path;

	oldpwd = get_cd_path(&util->env, "OLDPWD");
	path = ft_strdup(args[1]);
	if (path)
	{
		if (!ft_strcmp(path, "-") && oldpwd)
		{
			free(path);
			path = ft_strdup(oldpwd);
		}
		else
			return (free(path), 0);
		if (chdir(path) != 0)
		{
			util->code = 1;
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (free(path), 1);
		}
		util->code = 0;
		return (free(path), 1);
	}
	free(oldpwd);
	return (free(path), 0);
}

void	change_dir(t_exec_utils *util, char **args)
{
	if (args[1] && args[2])
	{
		util->code = 1;
		ft_putstr_fd("minishell: cd:", 2);
		ft_putendl_fd(" too many arguments", 2);
		return ;
	}
	if (home_cd(util, args) == 1)
		return ;
	if (oldpwd_cd(util, args) == 1)
		return ;
	if (path_cd(util, args))
		return ;
}
