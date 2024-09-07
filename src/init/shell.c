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

void	modify_exit_code(t_env **env, int code)
{
	t_env	*temp;
	t_env	*new;
	char	*code_str;

	temp = (*env);
	while (temp)
	{
		if (!ft_strcmp(temp->key, "?"))
		{
			code_str = ft_itoa(code);
			temp->value = code_str;
			return ;
		}
		temp = temp->next;
	}
	new = env_lstnew("?", code_str, 2);
	env_lstadd_back(env, new);
}

void free_token_list(t_token *token_list) {
    t_token *current;
    t_token *next;

    current = token_list;
    while (current != NULL) {
        next = current->next;

        // Free the value of the token if it's not NULL
        if (current->value) {
            free(current->value);
        }

        // Recursively free the sub_lexer if it exists
        if (current->sub_lexer) {
            free_token_list(current->sub_lexer->token_list);
            free(current->sub_lexer);  // Free the sub_lexer itself
        }

        // Free the current token
        free(current);

        // Move to the next token
        current = next;
    }
}

void	free_lexer(t_lexer *lexer) {
    if (lexer == NULL) {
        return;
    }

    // Free the token list
    free_token_list(lexer->token_list);

    // Free the lexer itself
    free(lexer);
}

int	init_shell(t_lexer *lex, t_exec_utils *util, t_env **env)
{
	char		*input;
	t_token		*token;
	t_syntax_tree	*tree;

	input = lex->util->input;
	if (input == NULL)
	{
		exit(util->code);
		return (1);
	}
	token = malloc(sizeof(t_token));
	init_lexer(input, &lex, &token, (*env));
	if (close_values(input, &lex, &util))
	{
		if (validate_lexer(&lex, &util) == 1)
		{
			tree = ft_calloc(1, sizeof(t_syntax_tree));
			init_parser(&lex, &tree);
			init_execute(tree, env, &util);
			free_ast(tree->branch);
			free(tree);
		}	
	}
	if (token)
		free_token(token);
	return (0);
}

void	prompt_loop(t_env *env)
{
	char			*input;
	t_lexer			*lex;
	t_exec_utils		*util;
	char			*code;

	util = malloc(sizeof(t_exec_utils));
	util->code = 0;
	lex = malloc(sizeof(t_lexer));
	lex->util = malloc(sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	while (1)
	{
		input = readline("\033[1;3142@minishell=> \033[0;0m");
		add_history(input);
		lex->util->input = input;
		if (init_shell(lex, util, &env))
			break ;
		modify_exit_code(&env, util->code);
		free(input);
		lex->util->rec_count = 0;
	}
	free(lex->util);
	free_lexer(lex);
	free(util);
	rl_clear_history();
}
