/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:29:24 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 06:39:58 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

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

void	export_arg_value(t_env **env, char *key, char *value)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(key, head->key))
		{
			internal_unset(env, key);
			break ;
		}
		head = head->next;
	}
	new = env_lstnew(key, value, 0);
	env_lstadd_back(env, new);
}

void	export_null_arg(t_env **env, char *arg)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(arg, head->key))
			return ;
		head = head->next;
	}
	new = env_lstnew(arg, "", 1);
	env_lstadd_back(env, new);

}

void	export_args(t_env **env, char *arg)
{
	char	*delim;
	char	*temp;
	char	*key;
	char	*value;

	temp = arg;
	delim = ft_strchr(temp, '=');
	if (!delim)
		export_null_arg(env, arg);
	if (delim)
	{
		key = get_key(arg);
		value = get_value(arg);
		export_arg_value(env, key, value);
		if (value)
			free(value);
		free(key);
	}
	
}

bool	validate_export_args(char *arg)
{
	if (ft_strchr(arg, '-') || ft_strchr(arg, '+'))
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	return (true);
}

void	handle_export_args(t_env **env, t_exec_utils **util, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!validate_export_args(args[i]))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(" :not a valid identifier", 2);
			(*util)->code = 2;
		}
		else
			export_args(env, args[i]);
	}
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
		handle_export_args(env, &util, args);
}
