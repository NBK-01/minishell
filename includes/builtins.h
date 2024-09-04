/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbk <nbk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:41:09 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/03 15:36:43 by nbk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "./minishell.h"
# include "./execute.h"

// IF ANY ENV GETS UNSET OR IS NULL DO CHECKS IN BUILTIN 
//COMMANDS TO RETURN ERRROS (SEE BASH)
// EXAMPLES: UNSET OLDPWD -> CD - SHOULD RE TURN AN ERROR CHECK IF OLDPWD 
//IS NULL WHEN CHDIRing INTO IT
// EXAMPLES: UNSETTING HOME ENV AND CD INTO HOME SHOULD NOT RETURN AND ERROR 
//BUT TAKE YOU BACK TO THE ROOT DIR (CHECK BASH FOR CONFIRMATION)
// CHECK FOR OTHER ODD BEHAVOIRS IN BASH.
// CAT | CAT | ls -> fully functional now.

void	exec_pwd(char **args, t_exec_utils **util);
void	change_dir(t_exec_utils *util, char **args);
int		handle_exit(t_exec_utils *util, char **args);
void	exec_env(t_env **env, char **args);
void	exec_unset(t_env **env, char **args);
void	internal_unset(t_env **env, char *key);
void	exec_export(t_env **env, t_exec_utils *util, char **args);
void	exec_echo(t_ast_node *node, t_exec_utils **util);

#endif
