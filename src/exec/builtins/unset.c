/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:21:00 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 15:58:15 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

void	free_env_node(t_env *node, int i)
{
	if (node->value)
		free(node->value);
	if (node->key)
		free(node->key);
	if (node && i == 0)
		free(node);
}

void	delete_env_node(t_env **env_list, const char *key, int i)
{
	t_env	*current;
	t_env	*prev;

	if (env_list == NULL || *env_list == NULL)
		return ;
	current = *env_list;
	prev = NULL;
	if (current != NULL && ft_strcmp(current->key, key) == 0)
	{
		*env_list = current->next;
		free_env_node(current, i);
		return ;
	}
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	prev->next = current->next;
	free_env_node(current, i);
}

void	internal_unset(t_env **env, char *key)
{
	if (env == NULL || key == NULL)
		return ;
	delete_env_node(env, key, 0);
}

void	exec_unset(t_env **env_list, char **keys)
{
	int	i;

	if (env_list == NULL || keys == NULL)
		return ;
	i = 1;
	while (keys[i])
	{
		delete_env_node(env_list, keys[i], 0);
		i++;
	}
}
