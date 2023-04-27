/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:56:14 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/09 20:16:38 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s;

	s = 0;
	if (dst && ft_strlen(dst) > dstsize)
		return (ft_strlen(src) + dstsize);
	while (dst && *dst != '\0' && s < dstsize)
	{
		dst++;
		s++;
	}
	while (*src != '\0')
	{
		s++;
		if (s < dstsize)
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	if (dst)
		*dst = '\0';
	return (s);
}
