#include "../includes/minishell.h"


void exec_unset(t_env **env, char **name)
{
    t_env *head; 
    t_env *prev;

    head = (*env);
    prev = NULL;
    while (head)
    {
        if (!ft_strcmp(head->key, name[1]))
        {
            if (prev == NULL)
                *env = head->next;
            else
                prev->next = head->next;

            // Free the current node
            free(head->key);
            free(head->value);
            free(head);
            
            // Return immediately after removing the item
            return;
        }
        prev = head;
        head = head->next;
    }
    printf("Environment variable '%s' not found.\n", name[1]);
}
