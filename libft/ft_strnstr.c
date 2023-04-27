/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:12:08 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/10 18:11:49 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*p1;
	char	*p2;
	size_t	l;

	p1 = (char *)haystack;
	p2 = (char *)needle;
	l = len;
	while (l > 0 && *p1 != '\0' && *p2 != '\0')
	{
		if (*p1 == *p2)
		{
			p1++;
			p2++;
			l--;
		}
		else
			return (ft_strnstr(haystack + 1, needle, len - 1));
	}
	if (*p2 == '\0')
		return ((char *)haystack);
	return (NULL);
}
