#include "../../../includes/builtins.h"
#include "../../../includes/lexer.h"
#include "../../../includes/ast.h"
#include "../../../includes/execute.h"


// void free_env(t_env *head) {
//     t_env* current = (*head);
//     t_env* nextNode;

//     while (current != NULL) {
//         nextNode = current->next; // Save the next node
//         free(current->key);            // Free the current node
// 	    free(current->value);
//         current = nextNode;       // Move to the next node
//     }
// }

// void cleanup_resources(t_exec_utils *exec, t_lex_utils *lex) {
//     if (exec->env != NULL) {
//         free_env(&exec->env);
//         exec->env = NULL; // Set pointer to NULL
//     }

//     if (lex->env != NULL) {
//         free_env(&lex->env);
//         lex->env = NULL;
//     }
// }
