/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:31:14 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:22:03 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execute.h"
#include "../../../includes/minishell.h"
#include "../../../includes/builtins.h"

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
