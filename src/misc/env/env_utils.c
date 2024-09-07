/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:52 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 19:42:32 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	modify_oldpwd(t_env **env, char *oldpwd)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(head->key, "OLDPWD"))
		{
			head->value = oldpwd;
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("OLDPWD", oldpwd, 0);
	env_lstadd_back(env, new);
}

void	modify_shell_lvl(t_env *env)
{
	t_env	*head;
	char	*level;
	int	nbr;
	t_env	*new;

	head = env;
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
		{
			nbr = ft_atoi(head->value);
			nbr += 1;
			level = ft_itoa(nbr);
			head->value = level;
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("SHLVL", "0", 0);
	env_lstadd_back(&env, new);
}

char	*get_key_exp(char *str)
{
	char	*temp;
	char	*delim;
	char	*key;

	temp = ft_strdup(str);
	delim = ft_strchr(temp, '=');
	if (delim != NULL)
	{
		*delim = '\0';
		key = ft_strdup(temp);
	}
	else
		key = ft_strdup(temp);
	free(temp);
	return (key);
}

char	*get_value_exp(char *str)
{
	char	*temp;
	char	*delim;
	char	*value;

	temp = ft_strdup(str);
	delim = ft_strchr(temp, '=');
	if (delim != NULL)
		value = ft_strdup(delim + 1);
	else
		value = NULL;
	free(temp);
	return (value);
}

int	exec_export_body(t_env **env, char **args)
{
	char	*key;
	char	*value;
	t_env	*new;
	int	flag;

	if (valid_export(args) == 1)
		return (1);
	if (!add_new_env(args, env))
		return (0);
	if (valid_export(args) > 1)
		return (export_multi_args(env, args));
	else
	{
		key = ft_strdup(args[1]);
		value = ft_strdup(args[3]);
	}
	change_env_values(env, value, key, &flag);
	if (flag)
	{
		new = env_lstnew(key, value, 0);
		env_lstadd_back(env, new);
	}
	return (10);
}
