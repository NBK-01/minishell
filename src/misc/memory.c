#include "../../includes/minishell.h"
#include "../../includes/token.h"
#include "../../includes/ast.h"


static void	free_tree(t_syntax_tree *tree)
{
	if (tree->branch)
		free_ast(tree->branch);
}



void	free_ast(t_ast_node *node)
{
	if (node)
	{
		if (node->tree_link)
			free_tree(node->tree_link);
		if (node->left)
			free_ast(node->left);
		if (node->right)
			free_ast(node->right);
		if (node->args)
			free_split(node->args);
		if (node->in)
			free(node->in);
		if (node->out)
			free(node->out);
		free(node);
	}
}


void free_token(t_token *token) {
    t_token *current = token;
    t_token *next_token;

    while (current != NULL) {
        next_token = current->next;
        if (current->value) {
            free(current->value);
        }
        free(current);
        current = next_token;
    }
}
void	free_env_list(t_env **env)
{
	t_env	*curr;
	t_env	*next;

	curr = (*env);
	while (curr)
	{
		next = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = next;
	}
}

void free_split(char **array)
{
    if (array)
    {
        char **temp = array;
        while (*temp)
        {
            free(*temp); // Free each string
            temp++;
        }
        free(array); // Free the array of strings itself
    }
}

