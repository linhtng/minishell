/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:32:23 by jhenriks          #+#    #+#             */
/*   Updated: 2023/02/14 19:49:00 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnbr(t_list *lst, int nbr)
{
	while (lst)
	{
		if (lst->content && *(int *)lst->content == nbr)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
