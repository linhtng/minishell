/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:43:11 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/08 20:49:38 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_heredoc(int signum)
{
	ft_putstr_fd("\n", 2);
	if (signum == SIGINT)
		g_exit_status = 1;
}

void	ignore_sigquit(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sigact, 0);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sigact;

	ignore_sigquit();
	ft_bzero(&sigact, sizeof(sigact));
	sigact.sa_handler = &sig_handler_heredoc;
	sigaction(SIGINT, &sigact, 0);
}
