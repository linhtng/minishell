/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:49:29 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/30 17:48:37 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit builtin, accepts single argument to specify the exit status
int	exit_shell(t_list **env_list, char **args)
{
	int	status;

	status = 0;
	ft_putstr_fd("exit\n", 1);
	if (args[0])
	{
		if (!ft_isnumstr(args[0]))
		{
			print_error(4, "exit: ", args[0], ": ",
				"numeric argument required");
			status = 255;
		}
		else if (args[1])
		{
			print_error(2, "exit: ", "too many arguments");
			return (1);
		}
		else
			status = (unsigned char)ft_atoi(args[0]);
	}
	clear_env_list(env_list);
	exit(status);
}
