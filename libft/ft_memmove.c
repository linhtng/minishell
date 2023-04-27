/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:09:32 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/02 19:13:06 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*p1;
	char	*p2;

	p1 = (char *)dst;
	p2 = (char *)src;
	if (dst > src)
	{
		while (len-- > 0)
			p1[len] = p2[len];
	}
	else
		ft_memcpy(p1, p2, len);
	return (p1);
}
