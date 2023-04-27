/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:04:27 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/02 19:01:53 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	s;

	s = 0;
	while (*src != '\0')
	{
		if (dstsize > 1)
		{
			*dst = *src;
			dst++;
			dstsize--;
		}
		src++;
		s++;
	}
	if (dstsize > 0)
		*dst = '\0';
	return (s);
}
