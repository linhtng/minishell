/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:49:29 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/02 18:19:43 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit builtin, accepts single argument to specify the exit status
void	exit_shell(t_list **env_list, char *n)
{
	int	status;

	status = 0;
	clear_env_list(env_list);
	ft_putstr_fd("exit\n", 1);
	if (n)
	{
		if (!ft_isnumstr(n))
		{
			print_error(4, "exit: ", n, ": ", "numeric argument required");
			exit(255);
		}
		status = (unsigned char)ft_atoi(n);
	}
	exit(status);
}
