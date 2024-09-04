/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:51:52 by nbk               #+#    #+#             */
/*   Updated: 2024/09/03 15:53:21 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	modify_oldpwd(t_env **env, char *oldpwd)
{
	t_env	*head;
	t_env	*new;

	head = (*env);
	while (head)
	{
		if (!ft_strcmp(head->key, "OLDPWD"))
		{
			head->value = ft_strdup(oldpwd);
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
	int		nbr;
	t_env	*new;

	head = env;
	while (head)
	{
		if (!ft_strcmp(head->key, "SHLVL"))
		{
			nbr = ft_atoi(head->value);
			nbr += 1;
			level = ft_itoa(nbr);
			head->value = ft_strdup(level);
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("SHLVL", "0", 0);
	env_lstadd_back(&env, new);
}
