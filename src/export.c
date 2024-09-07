/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:29:24 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 16:57:47 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/execute.h"

int	bubble_swap(t_env **current)
{
	char	*temp_content;
	char	*temp_key;
	int		temp_hidden;

	temp_content = (*current)->value;
	temp_key = (*current)->key;
	temp_hidden = (*current)->hidden;
	(*current)->key = (*current)->next->key;
	(*current)->value = (*current)->next->value;
	(*current)->hidden = (*current)->next->hidden;
	(*current)->next->key = temp_key;
	(*current)->next->value = temp_content;
	(*current)->next->hidden = temp_hidden;
	return (1);
}

void	bubble_sort(t_env **stack)
{
	int		swapped;
	t_env	*current;
	t_env	*last;

	last = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *stack;
		while (current->next != last)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swapped = bubble_swap(&current);
			}
			current = current->next;
		}
		last = current;
	}
}

int	valid_export(char **args)
{
	int	i;
	int	j;
	int	valid;

	i = 1;
	valid = valid_multi_args(args);
	if (ft_strchr(args[1], '-') || ft_strchr(args[1], '+'))
	{
		ft_putendl_fd(" not a valid identifier", 2);
		return (1);
	}
	if (valid && valid > 1)
		return (valid);
	if (valid_identifiers(args))
		return (1);
	return (0);
}

int	exec_export_2(t_env **env, char **args)
{
	int	flag;
	t_env	*head;
	t_env	*new;

	flag = 0;
	head = (*env);
	if (args)
	{
		if (exec_export_body(env, args) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	exec_export(t_env **env, t_exec_utils *util, char **args)
{
	t_env	*cpy;
	t_env	*head;
	t_env	*cpy_head;

	if (!args[1])
	{
		cpy = ft_lstcpy(env);
		bubble_sort(&cpy);
		head = cpy;
		cpy_head = head;
		while (head)
		{
			if (head->hidden == 1)
				printf("declare -x %s\n", head->key);
			if (head->hidden == 0)
				printf("declare -x %s=\"%s\"\n", head->key, head->value);
			head = head->next;
		}
		free_env_list(&cpy_head);
		return ;
	}
	else
		util->code = exec_export_2(env, args);
}
