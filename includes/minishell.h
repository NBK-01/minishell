/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:59 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/16 13:35:10 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include "../lib/includes/libft.h"
# include "./structs.h"

# define RESET "\033[0m"
# define GREEN "\033[32m"
# define ORANGE "\033[33m"
# define BOLD_RED "\033[1;31m"
/*/////////////////////////////////////////////////////////////
////////////		INITS			    //////////
////////////////////////////////////////////////////////////*/
///
void	export_null_arg(t_env **env, char *arg);
void	export_arg_value(t_env **env, char *key, char *value);
void	export_args(t_env **env, char *arg);
bool	validate_export_args(char *arg);
void	handle_export_args(t_env **env, t_exec_utils **util, char **args);
char	*get_prompt(t_env **env, int code);
char	*get_value(const char *str);
char	*get_key(char *str);
void	modify_pwd(t_env **env);
void	handle_eof(t_exec_utils *util);
void	free_shell(t_token *token, t_lexer *lex);
void	free_env_list(t_env **env);
void	free_split(char **split);
void	free_ast(t_ast_node *node);
void	free_lexer(t_lexer **lex);
void	free_token(t_token *token);
void	prompt_loop(t_env *env);
int		init_shell(t_lexer *lex, t_exec_utils *util, t_env **env);
void	l_recursive_print(t_lexer *lex, int id);
void	modify_oldpwd(t_env **env, char *oldpwd);
void	print_env(t_env **head);
void	split_env(char *env_str, char **key, char **value);
void	copy_env(t_env	**env_ll, char **env);
void	modify_shell_lvl(t_env *env);
void	signal_handler(void);
void	sigint_heredoc(int signalnum);

#endif
