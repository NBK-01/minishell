/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 03:10:21 by nbk               #+#    #+#             */
/*   Updated: 2024/09/11 08:39:20 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"
#include "../../../../includes/execute.h"

t_node	*append_node(t_node *head, char *data)
{
	t_node	*new_node;
	t_node	*current;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	if (!new_node->data)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (!head)
		return (new_node);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (head);
}

void	free_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}

void	expand_helper(t_expand *ex, t_env *env)
{
	(void)env;
	ex->text_start = ex->start;
	while (*ex->start && *ex->start != '$')
		ex->start++;
	ex->text_len = ex->start - ex->text_start;
	ex->text = ft_strndup(ex->text_start, ex->text_len);
	if (ex->text)
	{
		if (ex->list_head)
			ex->last_node = append_node(ex->last_node, ex->text);
		else
		{
			ex->last_node = append_node(NULL, ex->text);
			ex->list_head = ex->last_node;
		}
		free(ex->text);
	}
}

char	*get_env_value(const char *key, t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

void	free_ex(t_expand *ex)
{
	free_list(ex->list_head);
	free(ex->res);
	free(ex);
}
