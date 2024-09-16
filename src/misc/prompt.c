/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:18:54 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 12:14:17 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/structs.h"
#include "../../includes/minishell.h"
#include "../../includes/token.h"

char	*colorize(char *text, char *color_code)
{
	size_t	text_len;
	size_t	buffer_len;
	char	*colored_text;

	text_len = ft_strlen(text);
	buffer_len = ft_strlen(color_code) + text_len + ft_strlen(RESET) + 1;
	colored_text = (char *)malloc(buffer_len);
	ft_strcpy(colored_text, color_code);
	ft_strcat(colored_text, text);
	ft_strcat(colored_text, RESET);
	return (colored_text);
}

char	*no_env_prompt(char *code, char *user, char *arrow, char *term)
{
	char	*prompt;

	if (user)
		free(user);
	if (term)
		free(term);
	prompt = ft_strjoin_n(7, "42", "@", "mini ", "[", code, "] ", arrow);
	free(code);
	free(arrow);
	return (prompt);
}

char	*set_prompt(char *user, char *code, char *term)
{
	char	*prompt;
	char	*color_user;
	char	*color_code;
	char	*color_arrow;

	if (ft_strcmp(code, "0"))
		color_code = colorize(code, BOLD_RED);
	else
		color_code = colorize(code, GREEN);
	color_arrow = colorize("~> ", GREEN);
	free(code);
	if (!user || !term)
		return (no_env_prompt(color_code, user, color_arrow, term));
	color_user = colorize(user, GREEN);
	free(user);
	prompt = ft_strjoin_n(8, color_user, "@", term, " ",
			"[", color_code, "] ", color_arrow);
	free(color_user);
	free(term);
	free(color_code);
	free(color_arrow);
	return (prompt);
}

char	*get_prompt(t_env **env, int code)
{
	char	*user;
	char	*term;
	t_env	*head;
	char	*code_str;

	head = (*env);
	user = NULL;
	term = NULL;
	while (head)
	{
		if (!ft_strcmp(head->key, "USER"))
			user = ft_strdup(head->value);
		if (!ft_strcmp(head->key, "TERM"))
			term = ft_strdup(head->value);
		if (!ft_strcmp(head->key, "?"))
			code_str = ft_strdup(head->value);
		head = head->next;
	}
	(void)code;
	return (set_prompt(user, code_str, term));
}
