/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/05 13:05:32 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/ast.h"




int	main(int ac, char **av, char **env)
{
	t_env	*env_ll;

	env_ll = NULL;
	copy_env(&env_ll, env);
	(void)av;
	if (ac != 1)
		exit(printf("Invalid args\n"));
	else
		prompt_loop(env_ll);
}
