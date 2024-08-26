/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:19:15 by mhabbal           #+#    #+#             */
/*   Updated: 2024/08/26 16:19:16 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_home_dir(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "HOME=", 5) == 0)
            return(ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
        i++;
    }
}

void    handle_builtins(char *input, char **env)
{
    char    *home;

    home = get_home_dir(env);
    if (ft_strncmp(input, "cd", 2) == 0)
        change_dir(ft_substr(input, 3, ft_strlen(input) - 3), home);
    if ((ft_strcmp(input, "pwd") == 0))
        printf("%s\n", get_dir());
}
