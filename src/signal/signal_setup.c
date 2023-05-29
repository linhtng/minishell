/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                   	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:11:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/29 18:11:40 by thuynguy         ###   ########.fr       */
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

void	ignore_sigquit(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, 0);
}

void	setup_signals(void)
{
	struct sigaction	sigact;

	ignore_sigquit();
	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler;
	sigaction(SIGINT, &sigact, 0);
}

void	sig_handler_child(int signum)
{
	ft_putchar_fd('\n', 1);
	if (signum == SIGINT)
		g_exit_status = 130;
	else if (signum == SIGQUIT)
		g_exit_status = 131;
}

void	setup_signals_child(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler_child;
	sigaction(SIGINT, &sigact, 0);
	sigaction(SIGQUIT, &sigact, 0);
}
