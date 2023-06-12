/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:11:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/01 18:42:54 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	setup_signals(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		ft_putstr_fd("\n", 2);
	}
	else if (signum == SIGQUIT)
	{
		g_exit_status = 131;
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	setup_signals_child(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
}
