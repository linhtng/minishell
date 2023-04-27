/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:43:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/18 12:44:14 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoin(void *s1, const void *s2, size_t s1size, size_t s2size)
{
	char	*ret;
	size_t	size;

	size = s1size + s2size;
	if (size == 0 || (!s1 && !s2))
		return (NULL);
	ret = (char *)malloc(size * sizeof(char));
	if (ret)
	{
		if (s1)
		{
			ft_memcpy(ret, s1, s1size);
			free(s1);
		}
		ft_memcpy(ret + s1size, s2, s2size);
	}
	else if (s1)
		free(s1);
	return (ret);
}
