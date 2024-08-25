#ifndef LIST_H
# define LIST_H

# include "./libft.h"
# include "../../includes/structs.h"
# include "../../includes/minishell.h"

typedef struct s_list
{
	char				*content;
	struct s_list			*next;
}	t_list;

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);

t_lex_ll	*l_lstlast(t_lex_ll *lst);
t_lex_ll	*l_lstnew(int id);
void		l_lstadd_back(t_lex_ll **lst, t_lex_ll *new);


t_env		*env_lstlast(t_env *lst);
void		env_lstadd_back(t_env **env, char *key, char *value);
t_env		*env_lstnew(char *key, char *value);

#endif
