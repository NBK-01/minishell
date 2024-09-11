/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 09:17:01 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/10 18:17:52 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct s_mini
{
	int	mini_code;
	int	in_heredoc;
	int	cat;
}	t_mini;

extern t_mini	g_mini;

void	fork_handler(int signum);

#endif
