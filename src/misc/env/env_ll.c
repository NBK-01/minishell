/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:52:00 by nbk               #+#    #+#             */
/*   Updated: 2024/09/03 15:52:22 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *get_key(const char *str)
{
	char *temp = strdup(str);
	char *delim = strchr(temp, '=');
	char *key;

    if (delim != NULL) {
        *delim = '\0';
        key = strdup(temp); // Duplicate key
    } else {
        key = strdup(temp); // Duplicate whole string if no '='
    }
    free(temp);
    return key;
}

char *get_value(const char *str) {
    char *temp = strdup(str);
    char *delim = strchr(temp, '=');
    char *value;

    if (delim != NULL) {
        value = strdup(delim + 1); // Duplicate value part
    } else {
        value = NULL;
    }
    free(temp);
    return value;
}
#include "../../../includes/get_next_line.h"
#include <fcntl.h>

void copy_env(t_env **env_ll, char **env) {
    int i;
    char *key;
    char *value;
    t_env *new;
    

    i = 0;
    while (env[i]) {
        key = get_key(env[i]);
        value = get_value(env[i]);
        new = env_lstnew(key, value, 0);
        env_lstadd_back(env_ll, new);
        free(key);  // Free the duplicated key after adding to the list
        free(value); // Free the duplicated value after adding to the list
        i++;
    }
    new = env_lstnew("?", "0", 2);
    env_lstadd_back(env_ll, new);
    int	fd = open("/proc/self/stat", O_RDONLY);
    char *line;
    char **split = NULL;
    line = get_next_line(fd);
    if (line)
	    split = ft_split(line, ' ');
	
    if (split)
        new = env_lstnew("$", split[3], 2);
    else
        new = env_lstnew("$", "123", 2);
    env_lstadd_back(env_ll, new);
    (*env_ll)->og = env;
}
void	print_env(t_env **head)
{
	t_env	*current;

	current = (*head);
	while (current != NULL)
	{
		ft_putstr_fd(current->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
}
