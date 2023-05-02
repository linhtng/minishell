/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:10:55 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/02 20:16:50 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	n;

	n = 0;
	if (*args)
	{
		if (!ft_strncmp("-n", *args, 3))
		{
			n = 1;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args, 1);
			args++;
			if (*args)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}
