/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:22:26 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"
#include "../../includes/signals.h"

void	exit_helper(t_exec_utils **util)
{
	if (g_mini.mini_code)
	{
		(*util)->code = g_mini.mini_code;
	}
}

void	modify_exit_code(t_env *env, t_exec_utils *util)
{
	char	*str;
	t_env	*head;
	t_env	*new;

	exit_helper(&util);
	head = env;
	str = ft_itoa(util->code);
	while (head)
	{
		if (!ft_strcmp(head->key, "?"))
		{
			if (head->value)
				free(head->value);
			head->value = str;
			g_mini.mini_code = 0;
			return ;
		}
		head = head->next;
	}
	new = env_lstnew("?", str, 2);
	free(str);
	env_lstadd_back(&env, new);
	g_mini.mini_code = 0;
}

int	init_shell(t_lexer *lex, t_exec_utils *util, t_env **env)
{
	t_token			*token;
	t_syntax_tree	*tree;

	if (!lex->util->input)
		handle_eof(util);
	modify_exit_code((*env), util);
	token = malloc(sizeof(t_token));
	init_lexer(lex->util->input, &lex, &token, (*env));
	if (close_values(lex->util->input, &lex, &util))
	{
		if (validate_lexer(&lex, &util) == 1)
		{
			tree = ft_calloc(1, sizeof(t_syntax_tree));
			init_parser(&lex, &tree);
			lex->util->rec_count = 0;
			free_lexer(&lex);
			init_execute(tree, env, &util);
			free_ast(tree->branch);
			free(tree);
			free_token_ll(token);
		}
		else
			free_shell(token, lex);
	}
	return (0);
}

void	prompt_loop(t_env *env)
{
	char			*input;
	t_lexer			*lex;
	t_exec_utils	*util;
	char			*prompt;

	util = malloc(sizeof(t_exec_utils));
	util->code = 0;
	signal_handler();
	while (1)
	{
		lex = malloc(sizeof(t_lexer));
		lex->util = malloc(sizeof(t_lex_utils));
		lex->util->rec_count = 0;
		prompt = get_prompt(&env, util->code);
		input = readline(prompt);
		free(prompt);
		add_history(input);
		lex->util->input = input;
		if (init_shell(lex, util, &env))
			break ;
		free(input);
	}
	free(util);
}
