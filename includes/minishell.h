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
# include "../lib/includes/libft.h"
# include "./structs.h"

/*/////////////////////////////////////////////////////////////
////////////		INITS			    //////////
////////////////////////////////////////////////////////////*/
void	prompt_loop(t_env *env);
void	init_shell(t_lexer *lex, t_exec_utils *util,
			t_syntax_tree *tree, t_env **env);
void	l_recursive_print(t_lexer *lex, int id);
void	modify_oldpwd(t_env **env, char *oldpwd);
void	print_env(t_env **head);
void	split_env(char *env_str, char **key, char **value);
void	copy_env(t_env	**env_ll, char **env);
void	modify_shell_lvl(t_env **env);
void	cleanup_resources(t_exec_utils *exec, t_lex_utils *lex);
void	free_env(t_env **head);


#endif
