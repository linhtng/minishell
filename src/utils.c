/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:48:31 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/07 20:09:55 by jhenriks         ###   ########.fr       */
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

int	add_to_list(t_list **list, void *content)
{
	t_list	*new_elem;

	if (!list)
		return (0);
	new_elem = ft_lstnew(content);
	if (new_elem)
	{
		ft_lstadd_back(list, new_elem);
		return (1);
	}
	else
		return (0);
}
