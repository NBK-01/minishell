/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 19:39:10 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ast.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_ll;

	env_ll = NULL;
	copy_env(&env_ll, env);
	modify_shell_lvl(env_ll);
	(void)av;
	if (ac != 1)
		exit(printf("Invalid args\n"));
	else
		prompt_loop(env_ll);
	while (env_ll)
	{
		free(env_ll->key);
		free(env_ll->value);
		env_ll = env_ll->next;
	}
	free(env_ll);
}
