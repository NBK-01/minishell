/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhabbal <mhabbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:19:45 by mhabbal           #+#    #+#             */
/*   Updated: 2024/08/26 16:19:52 by mhabbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/token.h"

typedef struct s_queue_node {
    t_ast_node *node;
    int level;
    struct s_queue_node *next;
} t_queue_node;

// Queue structure
typedef struct s_queue {
    t_queue_node *front;
    t_queue_node *rear;
} t_queue;

// Function to initialize a queue
void init_queue(t_queue *q) {
    q->front = q->rear = NULL;
}

// Function to enqueue a node
void enqueue(t_queue *q, t_ast_node *node, int level) {
    t_queue_node *new_node = (t_queue_node *)malloc(sizeof(t_queue_node));
    new_node->node = node;
    new_node->level = level;
    new_node->next = NULL;
    if (q->rear) {
        q->rear->next = new_node;
    } else {
        q->front = new_node;
    }
    q->rear = new_node;
}

// Function to dequeue a node
t_queue_node *dequeue(t_queue *q) {
    if (q->front == NULL) return NULL;
    t_queue_node *temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

// Function to print the tree using BFS
void print_tree_bfs(t_ast_node *root) {
    if (root == NULL) return;

    t_queue q;
    init_queue(&q);
    enqueue(&q, root, 0);

    int current_level = 0;
    while (q.front != NULL) {
        t_queue_node *qnode = dequeue(&q);
        if (qnode == NULL) continue; // Avoid processing NULL nodes

        t_ast_node *node = qnode->node;
        int level = qnode->level;
        free(qnode);

        // Print new line when level changes
        if (level != current_level) {
            printf("\n");
            current_level = level;
        }

        // Print node type
        if (node) {
			printf("[ ");
			if (node->out)
				printf("OUT: %s --  ", node->out);
			if (node->in)
				printf("IN: %s --  ", node->in);
			for (int i = 0; node->args[i]; i++)
			{
				if (i != 0)
					printf(", ");
				printf("%s", node->args[i]);
			}
			printf(" ]");
            // printf("%d\n", node->id);
            // Enqueue children with next level
            if (node->left || node->right) {
                enqueue(&q, node->left, level + 1);
                enqueue(&q, node->right, level + 1);
            } else {
                // If node has no children, enqueue placeholders to maintain level structure
                enqueue(&q, NULL, level + 1);
                enqueue(&q, NULL, level + 1);
            }
        }
    }
	printf("\n");
}

void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	(*tree)->branch = p_build_tree((*lex)->token_list);
	if ((*tree)->branch->args)
		p_expand_tree((*tree)->branch);
}
