/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 09:18:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ast.h"
#include "../includes/signals.h"

int	g_mini_code;

int	main(int ac, char **av, char **env)
{
	t_env	*env_ll;

	signal_handler();
	env_ll = NULL;
	copy_env(&env_ll, env);
	modify_shell_lvl(env_ll);
	(void)av;
	if (ac != 1)
		exit(printf("Invalid args\n"));
	else
		prompt_loop(env_ll);
	free_env_list(&env_ll);
}
