/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:10:55 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/01 18:37:08 by jhenriks         ###   ########.fr       */
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
			printf("%s", *args);
			args++;
			if (*args)
				printf(" ");
		}
	}
	if (!n)
		printf("\n");
	return (0);
}
