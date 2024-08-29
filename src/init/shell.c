/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/29 16:16:23 by mhabbal          ###   ########.fr       */
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

void	init_shell(t_env *env)
{
	char	*input;
	t_lexer	*lex;
	t_token	*token;
	t_syntax_tree *tree;
	t_exec_utils *util;

	util = malloc(sizeof(t_exec_utils));
	util->code = 0;
	tree = malloc(sizeof(t_syntax_tree));
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	token = malloc(sizeof(t_token));
	while (1)
	{
		input = readline("\033[1;31mmhabbal&nkanaan@minishell=> \033[0;0m");
		add_history(input);
		//handle_builtins(input, env);
		init_lexer(input, &lex, &token, env);
		if (close_values(input, &lex, &util))
		{
			if (validate_lexer(&lex, &util) == 1)
			{
				init_parser(&lex, &tree);
				init_execute(tree, env, &util);
			}	
		}
		char *test = ft_itoa(util->code);
		t_env	*temp;
		temp = env;
		int	flag1 = 0;
		while (temp)
		{
			if (!ft_strcmp(temp->key, "?"))
			{
				temp->value = ft_strdup(test);
				flag1 = 1;
			}
			temp = temp->next;
		}
		if (!flag1)
			env_lstadd_back(&env, "?", test);
		free(input);
		env->code = util->code;
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	}
}
