/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:00:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/30 20:01:12 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstprev(t_list *first, t_list *lst)
{
	while (first && lst)
	{
		if (first->next == lst)
			return (first);
		first = first->next;
	}
	return (NULL);
}
