/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:31:14 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 16:56:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/execute.h"

int	valid_multi_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (ft_isalpha(args[i][0]))
			i++;
		else
			return (0);
	}
	return (i);
}

int	valid_identifiers(char **args)
{
	if (!ft_isalpha(args[1][0]))
	{
		ft_putendl_fd(" not a valid identifier", 2);
		return (1);
	}
	if (args[1] && args[2] && args[3])
	{
		if (args[2][0] != '=')
		{
			ft_putendl_fd(" not a valid identifier", 2);
			return (1);
		}
	}
	return (0);
}

int	export_multi_args(t_env **env, char **args)
{
	int		i;
	t_env	*head;
	t_env	*new;

	i = 0;
	while (args[++i])
	{
		head = (*env);
		while (head)
		{
			if (ft_strcmp(head->key, args[i]))
			{
				new = env_lstnew(args[i], "", 1);
				env_lstadd_back(env, new);
				break ;
			}
			head = head->next;
		}
	}
	return (0);
}

void	change_env_values(t_env **env, char *value, char *key, int *flag)
{
	t_env	*head;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(head->key, key))
		{
			if (head->hidden == 1)
			{
				internal_unset(env, key);
				*flag = 1;
				break ;
			}
			else
			{
				head->value = ft_strdup(value);
				*flag = 0;
				break ;
			}
		}
		else
			*flag = 1;
		head = head->next;
	}
}

int	add_new_env(char **args, t_env **env)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	if (args[2] == NULL)
	{
		while (head)
		{
			if (ft_strcmp(head->key, args[1]))
			{
				new = env_lstnew(args[1], "", 1);
				env_lstadd_back(env, new);
				return (0);
			}
			head = head->next;
		}
	}
	return (1);
}
