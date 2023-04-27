/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:09:10 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/30 20:09:30 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstpos(t_list *first, t_list *lst)
{
	int	n;

	if (!first || !lst)
		return (0);
	n = 1;
	while (lst != first)
	{
		n++;
		first = first->next;
	}
	if (first)
		return (n);
	else
		return (0);
}
