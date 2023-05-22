/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:31 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/22 19:26:47 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// prints n strings, passed as arguments, to STDERR
// strings are not separated by spaces, newline is added at end
void	print_error(int n, ...)
{
	va_list	msg;

	ft_putstr_fd("minishell: ", 2);
	va_start(msg, n);
	while (n-- > 0)
		ft_putstr_fd(va_arg(msg, char *), 2);
	va_end(msg);
	ft_putchar_fd('\n', 2);
}

int	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
