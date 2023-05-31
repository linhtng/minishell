/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:43:11 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/30 18:17:41 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sig_handler_heredoc(int signum)
{
	ft_putchar_fd('\n', 1);
	if (signum == SIGINT)
		g_exit_status = 1;
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sigact;

	ignore_sigquit();
	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler_heredoc;
	sigaction(SIGINT, &sigact, 0);
}
