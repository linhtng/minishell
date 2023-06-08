/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:54:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/01 18:40:51 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_echoctl(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, t);
}

void	reset_echoctl(struct termios *t)
{
	t->c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, t);
}

void	ctrl_d_signal(void)
{
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

void	sigquit_child(void)
{
	signal(SIGQUIT, SIG_DFL);
}
