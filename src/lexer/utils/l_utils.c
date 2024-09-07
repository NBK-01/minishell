/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:07:38 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 18:12:11 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

char *get_env_value(const char *key, t_env *env);


t_node *append_node(t_node *head, const char *data) {
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node) return NULL;
    new_node->data = strdup(data);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;

    if (!head) {
        return new_node;
    }

    t_node *current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;

    return head;
}

void free_list(t_node *list_head) {
    t_node *current = list_head;
    while (current) {
        t_node *next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

// Function to expand variables in a token's value
char *expand_variables(char *value, t_lex_utils *util, t_env *env) {
    if (!util->expand) {
        return ft_strdup(value);
    }

    t_node *list_head = NULL;
    t_node *last_node = NULL;
    const char *start = value;

    while (*start) {
        if (*start == '$') {
            start++;
	    if (*start == '\0' || *start == ' ')
	    {
			list_head = append_node(list_head, "$");
			last_node = list_head;
	    }
if (*start == '$')
	    {
				start++;
				char *pid = get_env_value("$", env);
				if (pid)
				{
					list_head = append_node(list_head, pid);
					last_node = list_head;
				}
			}

            if (*start == '?') {
                start++;
                // Extract exit code from environment
                char *exit_code = get_env_value("?", env); // Assume '?' is the key for exit code
                if (exit_code) {
                    list_head = append_node(list_head, exit_code);
                    last_node = list_head;
                }
                // Skip if exit code is NULL
            } else {
                const char *var_start = start;
                while (*start && (ft_isalnum(*start) || *start == '_')) {
                    start++;
                }
                size_t var_len = start - var_start;
                if (var_len > 0) {
                    char *var_name = strndup(var_start, var_len);
                    if (var_name) {
                        char *env_value = get_env_value(var_name, env);
                        free(var_name);
                        if (env_value && strlen(env_value) > 0) {
                            list_head = append_node(list_head, env_value);
                            last_node = list_head;
                        }
                        free(env_value);
                    }
                }
                // If the variable name is empty or variable is unresolved, skip it
            }
        } else {
            const char *text_start = start;
            while (*start && *start != '$') {
                start++;
            }
            size_t text_len = start - text_start;
            char *text = strndup(text_start, text_len);
            if (text) {
                if (list_head) {
                    last_node = append_node(last_node, text);
                } else {
                    list_head = last_node = append_node(NULL, text);
                }
                free(text);
            }
        }
    }

    // If no text or variables were added, return an empty string
    if (!list_head) {
        return ft_strdup("");
    }

    // Concatenate all nodes into a single string
    size_t total_length = 0;
    t_node *current = list_head;
    while (current) {
        total_length += strlen(current->data);
        current = current->next;
    }

    char *result = malloc(total_length + 1);
    if (!result) {
        free_list(list_head);
        return NULL;
    }

    char *ptr = result;
    current = list_head;
    while (current) {
        size_t data_len = strlen(current->data);
        memcpy(ptr, current->data, data_len);
        ptr += data_len;
        current = current->next;
    }
    *ptr = '\0';

    free_list(list_head);
    return result;
}

char *get_env_value(const char *key, t_env *env) {
   
	t_env *head;

	head = env;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return NULL;
}

int	l_token_count(t_lexer *lex, t_token *token, t_env *env)
{
	int		hits;
	char	**matches;
	char	*expanded;

	token = lex->token_list;
	while (token)
	{
		if (token->type == TOKEN)
		{
			matches = l_glob(token->value, &hits);
			if (hits > 0)
				l_handler_wildcards(token, hits, matches);
			else
				token->value = l_remove_quotes(token);
			expanded = expand_variables(token->value, lex->util, env);
			if (expanded)
			{
				free(token->value);
				token->value = expanded;
			}	
		}
		token = token->next;
	}
	return (0);
}

void	l_tokenize_words(t_lexer *lex, t_token *token, int type)
{
	if (type == TYPE_ESC)
	{
		token->value[lex->util->j++] = ++(*lex->util->input_ptr);
		token->type = TOKEN;
	}
	else if (type == TYPE_WORD)
	{
		token->value[lex->util->j++] = lex->util->c;
		token->type = TOKEN;
	}
}

void	l_tokenize_next(t_lexer *lex, t_token **token, int type, int len)
{
	if (lex->util->j > 0)
	{
		(*token)->value[lex->util->j] = '\0';
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
		lex->util->j = 0;
	}
	if (type != TYPE_SPACE)
	{
		(*token)->value[0] = type;
		(*token)->value[1] = '\0';
		(*token)->type = type;
		(*token)->next = ft_calloc(1, sizeof(t_token));
		if ((*token)->next == NULL)
			return ;
		init_token((*token)->next, len - lex->util->i, (*token)->id);
		*token = (*token)->next;
	}
}

int	validate_lexer(t_lexer **lex, t_exec_utils **utils)
{
	t_token	*temp;

	temp = (*lex)->token_list;
	if (!ft_strcmp(temp->value, "|") || !ft_strcmp(temp->value, "||")
		|| !ft_strcmp(temp->value, "&&") || !ft_strcmp(temp->value, ">>")
		|| !ft_strcmp(temp->value, ">") || !ft_strcmp(temp->value, ";"))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putendl_fd("\'", 2);
		(*utils)->code = 2;
		return (0);
	}
	if (!ft_strcmp(temp->value, "<") || !ft_strcmp(temp->value, "<<"))
	{
		if (!temp->next || temp->next->type != TYPE_WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token", 2);
			ft_putstr_fd(" `", 2);
			ft_putstr_fd(temp->value, 2);
			ft_putendl_fd("\'", 2);
			(*utils)->code = 2;
			return (0);
		}
	}
	while (temp)
	{
		if (temp->type == TYPE_LPAREN)
		{
			if (!temp->sub_lexer || !temp->sub_lexer->token_list->value[0])
			{

				ft_putstr_fd("minishell: syntax error near unexpected token", 2);
				ft_putstr_fd(" `", 2);
				ft_putstr_fd(temp->value, 2);
				ft_putendl_fd("\'", 2);
				(*utils)->code = 2;
				return (0);	
			}
			if (!validate_lexer(&temp->sub_lexer, utils))
				return (0);
		}
		if (temp->next)
		{
			if (!ft_strcmp(temp->next->value, ";"))
			{
				if (temp->type != TYPE_WORD)
				{

					ft_putstr_fd("minishell: syntax error near unexpected token", 2);
					ft_putstr_fd(" `", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putendl_fd("\'", 2);
					(*utils)->code = 2;
					return (0);
				}
			}
			if (temp->next->type == TYPE_PIPE || !ft_strcmp(temp->next->value, "||")
				|| !ft_strcmp(temp->next->value, "&&") || !ft_strcmp(temp->next->value, ">>")
				|| !ft_strcmp(temp->next->value, ">") || !ft_strcmp(temp->next->value, "<")
				|| !ft_strcmp(temp->next->value, "<<"))
			{
				if (!temp->next->next)
				{
					ft_putstr_fd("minishell: syntax error near unexpected token", 2);
					ft_putstr_fd(" `", 2);
					ft_putstr_fd(temp->value, 2);
					ft_putendl_fd("\'", 2);
					(*utils)->code = 2;
					return (0);
				}
                if (temp->next->type == TYPE_PIPE)
                {
                    if (temp->type != TYPE_WORD && (temp->next->next->type != TYPE_LSHIFT || temp->next->next->type != TYPE_RSHIFT
                        || temp->next->next->type != TYPE_WORD || temp->next->next->type != TYPE_HEREDOC || temp->next->next->type != TYPE_APPEND))
                        {
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
						(*utils)->code = 2;
						return (0);
                        }
                }
				else if (!ft_strcmp(temp->next->value, ">>")
				|| !ft_strcmp(temp->next->value, ">") || !ft_strcmp(temp->next->value, "<")
				|| !ft_strcmp(temp->next->value, "<<"))
                {
                    if ((temp->type != TYPE_WORD || temp->type != TYPE_PIPE) && temp->next->next->type != TYPE_WORD)
				    {
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
					    (*utils)->code = 2;
					    return (0);
				    } 
                }
                else if (!ft_strcmp(temp->next->value, "||")
				|| !ft_strcmp(temp->next->value, "&&"))
                {
                    if (temp->type != TYPE_WORD && temp->next->next->type != TYPE_WORD)
				    {
						ft_putstr_fd("minishell: syntax error near unexpected token", 2);
						ft_putstr_fd(" `", 2);
						ft_putstr_fd(temp->value, 2);
						ft_putendl_fd("\'", 2);
					    (*utils)->code = 2;
					    return (0);
				    } 
                }
			} 
		}
		temp = temp->next;
	}
	return (1);
}
