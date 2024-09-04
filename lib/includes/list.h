/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:24:40 by nbk               #+#    #+#             */
/*   Updated: 2024/09/04 15:38:34 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "./libft.h"
# include "../../includes/structs.h"
# include "../../includes/minishell.h"

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
}	t_list;

t_env		*env_lstlast(t_env *lst);
t_env		*env_lstnew(char *key, char *value, int hidden);
t_lex_ll	*l_lstlast(t_lex_ll *lst);
t_lex_ll	*l_lstnew(int id);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(char *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst);
void		env_lstdelone(t_env *env);
int			ft_lstsize(t_list *lst);
void		ft_lstclear(t_list **lst);
void		l_lstadd_back(t_lex_ll **lst, t_lex_ll *new);
void		env_lstadd_back(t_env **env, t_env *new);
t_env		*ft_lstcpy(t_env **stack);

#endif
