#ifndef EXECUTE_H
# define EXECUTE_H
# include "./minishell.h"
# include "./get_next_line.h"
# include "./ast.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>



int	init_execute(t_syntax_tree *tree, t_env **env, t_exec_utils **util);
char	*get_path(char **s_cmd, t_env **env);
int	e_traverse_tree(t_ast_node *node, t_exec_utils *util, t_env **env);

void	e_pipeline(t_ast_node *node, t_exec_utils *util, t_env **env);
void	e_pipeline_parent(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2]);
void	e_pipeline_child(t_ast_node *node, t_exec_utils *util, int *pid, int fd[2]);
void	e_pipeline_status(int pid1, int pid2, int *status, t_exec_utils *util);
void	copy_list_to_array(t_env *head, char **arr);
int	get_list_length(t_env *head);
char	**allocate_array(int size);

void	e_redirection(t_ast_node *node, t_exec_utils *util);
void 	handle_doc(char *lim, int pipefd[2]);

int	e_simple_command(t_ast_node *node, t_exec_utils *util, t_env **env, char *path);

void	e_operator_and(t_ast_node *node, t_exec_utils *util, t_env **env);
void	e_operator_or(t_ast_node *node, t_exec_utils *util, t_env **env);

#endif
