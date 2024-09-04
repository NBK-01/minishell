/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 21:55:12 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

void	print_lex(t_lexer **lexer, int id)
{
	if (!(*lexer))
		return ;
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

void	restore_prompt(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	ctrl_c_pressed(int signal_num)
{
	(void)signal_num;
	// rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

/*
	If a process is terminated by signal N, the exit status is usually 128 + N
*/
void	ctrl_c_pressed_child(int signal_number)
{
	(void)signal_number;
	write(1, "\n", 1);
}

/*
	-redirects ctrl-c into it's functions
	-redirects ctrl-\ into ignore
*/
void	setup_signals(void)
{
	signal(SIGINT, ctrl_c_pressed);
	signal(SIGQUIT, SIG_IGN);
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
		setup_signals();
		add_history(input);
		init_lexer(input, &lex, &token, env);
		close_values(input, &lex, &util);
		init_parser(&lex, &tree);
		init_execute(tree, &env, &util);
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
		{
			t_env *new = env_lstnew("?", test, 2);
			env_lstadd_back(&env, new);
		}
		if (!input)
			break ;
		free(input);
		env->code = util->code;
		lex->util->clock = 0;
		lex->util->rec_count = 0;
	}
}
