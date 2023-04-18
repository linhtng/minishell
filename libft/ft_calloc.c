/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:56:26 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/14 18:56:15 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;
	size_t	t;

	i = 0;
	t = 0;
	while (i++ < count)
	{
		t += size;
		if (t < size)
			return (NULL);
	}
	p = malloc(size * count);
	if (p)
		ft_bzero(p, size * count);
	return (p);
}
