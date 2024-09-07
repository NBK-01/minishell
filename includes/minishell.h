/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:59 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/04 17:07:02 by nkanaan          ###   ########.fr       */
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

/*/////////////////////////////////////////////////////////////
////////////		INITS			    //////////
////////////////////////////////////////////////////////////*/
void	free_env_list(t_env **env);
void	free_split(char **split);
void	free_ast(t_ast_node *node);
void	free_lexer(t_lexer *lex);
void	free_token(t_token *token);
void	prompt_loop(t_env *env);
int	init_shell(t_lexer *lex, t_exec_utils *util, t_env **env);
void	l_recursive_print(t_lexer *lex, int id);
void	modify_oldpwd(t_env **env, char *oldpwd);
void	print_env(t_env **head);
void	split_env(char *env_str, char **key, char **value);
void	copy_env(t_env	**env_ll, char **env);
void	modify_shell_lvl(t_env *env);
void	signal_handler(void);
void	sigint_heredoc(int signalnum);

#endif
