/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 21:17:46 by nbk              ###   ########.fr       */
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
		init_shell(env_ll);
}
