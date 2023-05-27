/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:54:05 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/25 20:55:42 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	setup_signals(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler;
	sigaction(SIGINT, &sigact, 0);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
		rl_on_new_line();
}

void	setup_signals_parent(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler_parent;
	sigaction(SIGINT, &sigact, 0);
	sigaction(SIGQUIT, &sigact, 0);
}
