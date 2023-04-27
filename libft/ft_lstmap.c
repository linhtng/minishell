/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:14:42 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/07 00:08:42 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*node;

	new = NULL;
	while (lst && f && del)
	{
		if (!new)
			new = ft_lstnew(f(lst->content));
		else
		{
			node = ft_lstnew(f(lst->content));
			if (node)
				ft_lstadd_back(&new, node);
			else
			{
				ft_lstclear(&new, del);
				break ;
			}
		}
		lst = lst->next;
	}
	return (new);
}
