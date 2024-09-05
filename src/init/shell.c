/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:29:58 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/05 13:05:22 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/lexer.h"
#include "../../includes/ast.h"
#include "../../includes/execute.h"

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
	}
	free(code);
}

void free_env_list(t_env **head) {
    t_env *current = (*head);
    t_env *next_node;

    while (current != NULL)
	{
        next_node = current->next; // Save the next node
        free(current->key);        // Free the key string
        free(current->value);
	free(current);      // Free the value string
        current = next_node;       // Move to the next node
    }
}

void free_treee(t_ast_node *head) {
    t_ast_node *node;

	node = head;
    if (node == NULL) {
        return;
    }

    // Recursively free the left and right subtrees
    if (node->left)
	free_treee(node->left);
    if (node->right)
        free_treee(node->right);

    for (size_t i = 0; node->args[i]; ++i) {
        free(node->args[i]);
    }
    
    free(node->args);
    free(node);
}

void	free_lex(t_lexer **lexer)
{
	t_lexer *lex;

	lex = (*lexer);
	if (!lex)
		return ;
	if (lex->util)
		free(lex->util);
	if (lex->token_list)
		free_token_ll(lex->token_list);
	free(lex);
}

void	free_lexer_lll(t_lexer **lexer)
{
	if ((*lexer))
		return ;
	while ((*lexer)->token_list)
	{
		if ((*lexer)->token_list->sub_lexer)
			free_lexer_lll(&(*lexer)->token_list->sub_lexer);
		free((*lexer)->token_list);
		free((*lexer));
	}
}

void	free_lexer_ll(t_lexer *lexer)
{
    t_token *current_token;
    t_token *next_token;

    if (!lexer)
        return;

	if (lexer->token_list)
		current_token = lexer->token_list;
    while (current_token)
    {
        next_token = current_token->next;
        
        if (current_token->sub_lexer)
        {
            free_lexer_ll(current_token->sub_lexer);
        }

        free(current_token->value);
        free(current_token);

        current_token = next_token;
    }

    // Free the lexer struct itself
    free(lexer);
}

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

void	free_ast(t_ast_node *node)
{
	int	i = 0;
	if (!node)
		return ;
	if (node->right)
		free_ast(node->right);
	if (node->left)
		free_ast(node->left);

	if (node->args && node->args[0])
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	free(node);
}


void	prompt_loop(t_env *env)
{
	char			*input;
	t_lexer			*lex;
	t_syntax_tree	*tree;
	t_exec_utils	*util;

	modify_shell_lvl(&env);
	util = ft_calloc(1, sizeof(t_exec_utils));
	util->code = 0;
	tree = ft_calloc(1, sizeof(t_syntax_tree));
	lex = ft_calloc(1, sizeof(t_lexer));
	lex->util = ft_calloc(1, sizeof(t_lex_utils));
	lex->util->rec_count = 0;
	while (1)
	{
		input = readline("\033[1;31mmhabbal&nkanaan@minishell=> \033[0;0m");
		add_history(input);
		lex->util->input = input;
		init_shell(lex, util, tree, &env);
		modify_exit_code(util, env);
		if (!input)
			break ;
		free(input);
		env->code = util->code;
		lex->util->rec_count = 0;
	}
	free(util);
	free_env_list(&env);
}
