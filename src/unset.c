/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:00 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 19:16:25 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execute.h"

void	free_env_node(t_env *node)
{
	if (node)
		free(node);
}

void	delete_env_node(t_env **env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (env_list == NULL || *env_list == NULL)
		return ;
	current = *env_list;
	prev = NULL;
	if (current != NULL && strcmp(current->key, key) == 0)
	{
		*env_list = current->next;
		free_env_node(current);
		return ;
	}
	while (current != NULL && strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	free_env_node(current);
}

void	internal_unset(t_env **env, char *key)
{
	if (env == NULL || key == NULL)
		return ;
	delete_env_node(env, key);
}

void	exec_unset(t_env **env_list, char **keys)
{
	int	i;

	if (env_list == NULL || keys == NULL)
		return ;
	i = 1;
	while (keys[i])
	{
		delete_env_node(env_list, keys[i]);
		i++;
	}
}
