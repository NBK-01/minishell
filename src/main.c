/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/10 18:18:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ast.h"
#include "../includes/signals.h"

t_mini	g_mini;

void	init_signal(void)
{
	g_mini.mini_code = 0;
	g_mini.in_heredoc = 0;
	g_mini.cat = 0;
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_ll;

	init_signal();
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
