/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <thuynguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:43:11 by thuynguy          #+#    #+#             */
/*   Updated: 2023/06/01 18:41:00 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_heredoc(int signum)
{
	printf("\n");
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
