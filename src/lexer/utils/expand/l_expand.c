/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:10:49 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/11 08:39:40 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"
#include "../../../../includes/execute.h"

void	expand_exit_code(t_expand *ex, t_env *env)
{
	ex->start++;
	ex->exit_code = get_env_value("?", env);
	if (ex->exit_code)
	{
		ex->list_head = append_node(ex->list_head, ex->exit_code);
		ex->last_node = ex->list_head;
	}
}

void	expand_var(t_expand *ex, t_env *env)
{
	ex->var_start = ex->start;
	while (*ex->start && (ft_isalnum(*ex->start)
			|| *ex->start == '_'))
		ex->start++;
	ex->len = ex->start - ex->var_start;
	if (ex->len > 0)
	{
		ex->var_name = ft_strndup(ex->var_start, ex->len);
		if (ex->var_name)
		{
			ex->env_value = get_env_value(ex->var_name, env);
			if (ex->var_name)
				free(ex->var_name);
			if (ex->env_value && ft_strlen(ex->env_value) > 0)
			{
				ex->list_head = append_node(ex->list_head,
						ex->env_value);
				ex->last_node = ex->list_head;
			}
		}
	}
}

void	expand_single(t_expand *ex, t_env *env)
{
	ex->start++;
	if (*ex->start == '\0' || *ex->start == ' ')
	{
		ex->list_head = append_node(ex->list_head, "$");
		ex->last_node = ex->list_head;
	}
	if (*ex->start == '$')
	{
		ex->start++;
		ex->pid = get_env_value("$", env);
		if (ex->pid)
		{
			ex->list_head = append_node(ex->list_head, ex->pid);
			ex->last_node = ex->list_head;
		}
	}
	if (*ex->start == '?')
		expand_exit_code(ex, env);
	else
		expand_var(ex, env);
}

int	finalize_expansion(t_expand *ex)
{
	ex->total_len = 0;
	ex->curr = ex->list_head;
	while (ex->curr)
	{
		ex->total_len += ft_strlen(ex->curr->data);
		ex->curr = ex->curr->next;
	}
	ex->res = malloc(ex->total_len + 1);
	if (!ex->res)
	{
		free_list(ex->list_head);
		free(ex->res);
		free(ex);
		return (1);
	}
	ex->ptr = ex->res;
	ex->curr = ex->list_head;
	while (ex->curr)
	{
		ex->data_len = ft_strlen(ex->curr->data);
		ft_memcpy(ex->ptr, ex->curr->data, ex->data_len);
		ex->ptr += ex->data_len;
		ex->curr = ex->curr->next;
	}
	return (0);
}

char	*expand_variables(char *value, int exp, t_env *env)
{
	t_expand	*ex;
	char		*res;

	ex = ft_calloc(1, sizeof(t_expand));
	if (!exp)
	{
		free(ex);
		return (ft_strdup(value));
	}
	ex->start = value;
	while (*ex->start)
	{
		if (*ex->start == '$')
			expand_single(ex, env);
		else
			expand_helper(ex, env);
	}
	if (!ex->list_head)
		return (free(ex), ft_strdup(""));
	if (finalize_expansion(ex) == 1)
		return (free(ex), NULL);
	*ex->ptr = '\0';
	res = ft_strdup(ex->res);
	free_ex(ex);
	return (res);
}
