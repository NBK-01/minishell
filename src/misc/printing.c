/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:06:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 15:38:43 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"
#include "../../includes/minishell.h"
#include "../../includes/token.h"

void	modify_pwd(t_env **env)
{
	char	*pwd;
	t_env	*head;
	t_env	*new;

	head = (*env);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	while (head)
	{
		if (!ft_strcmp(head->key, "PWD"))
		{
			if (head->value)
				free(head->value);
			head->value = ft_strdup(pwd);
			free(pwd);
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("PWD", pwd, 2);
	free(pwd);
	env_lstadd_back(env, new);
}

void	free_split(char **array)
{
	char	**temp;

	if (array)
	{
		temp = array;
		while (*temp)
		{
			free(*temp);
			temp++;
		}
		free(array);
	}
}

void	free_shell(t_token *token, t_lexer *lex)
{
	free_token_ll(token);
	free(lex->util);
	free(lex);
}

void	handle_eof(t_exec_utils *util)
{
	ft_putstr_fd("exit\n", 1);
	exit(util->code);
}
