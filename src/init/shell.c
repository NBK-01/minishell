/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 19:43:24 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

void print_lex(t_lexer **lexer, int id)
{
	if (!(*lexer))
		return;
	while ((*lexer)->token_list)
	{
		if (id == 0)
			printf("Main Level %d: %s\n", id, (*lexer)->token_list->value);
		else
			printf("Sub Level %d: %s\n", id, (*lexer)->token_list->value);
		if ((*lexer)->token_list->sub_lexer)
			print_lex(&(*lexer)->token_list->sub_lexer, id + 1);
		(*lexer)->token_list = (*lexer)->token_list->next;
	}
}

void	modify_exit_code(t_exec_utils *util, t_env *env)
{
	char	*code;
	int		flag;
	t_env	*temp;
	t_env	*new;

	code = ft_itoa(util->code);
	temp = env;
	flag = 0;
	while (temp)
	{
		if (!ft_strcmp(temp->key, "?"))
		{
			temp->value = ft_strdup(code);
			flag = 1;
		}
		temp = temp->next;
	}
	if (!flag)
	{
		new = env_lstnew("?", code, 2);
		env_lstadd_back(&env, new);
		free(code);
	}
	free(code);
}

void	init_shell(t_lexer *lex, t_exec_utils *util,
				t_syntax_tree *tree, t_env **env)
{
	char	*input;
	t_token	*token;

	input = lex->util->input;
	token = malloc(sizeof(t_token));
	init_lexer(input, &lex, &token, (*env));
	if (close_values(input, &lex, &util))
	{
		if (validate_lexer(&lex, &util) == 1)
		{
			init_parser(&lex, &tree);
			init_execute(tree, env, &util);
		}	
	}
}

void	prompt_loop(t_env *env)
{
	char			*input;
	t_lexer			*lex;
	t_syntax_tree	*tree;
	t_exec_utils	*util;

	util = malloc(sizeof(t_exec_utils));
	util->code = 0;
	tree = ft_calloc(1, sizeof(t_syntax_tree));
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	while (1)
	{
		input = readline("\033[1;3142@minishell=> \033[0;0m");
		add_history(input);
		lex->util->input = input;
		init_shell(lex, util, tree, &env);
		modify_exit_code(util, env);
		if (!input)
			break ;
		free(input);
		lex->util->rec_count = 0;
		if (tree && tree->branch)
			free_ast(tree->branch);
		free_token_ll(lex->token_list);
	}
	free(lex->util);
	free(util);
}
