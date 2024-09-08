/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:52 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 16:14:13 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_env_list(t_env *list)
{
	while (list)
	{
		if (list->hidden == 0)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
}

void	exec_env(t_env **env, char **args)
{
	t_env	*head;
	char	*delim;

	head = (*env);
	if (!args[1])
		print_env_list((*env));
	if (args[1])
	{
		delim = ft_strchr(args[1], '$');
		while (head)
		{
			if (delim)
			{
				if (!ft_strcmp(delim + 1, head->key))
				{
					printf("%s\n", head->value);
					return ;
				}
			}
			head = head->next;
		}
		printf("env: %s: no such file or directory\n", args[1]);
	}
}