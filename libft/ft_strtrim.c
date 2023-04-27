/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:45:11 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/15 14:24:39 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	f_trimstart(char *s1, const char *set)
{
	size_t	i;
	char	*s;

	i = 0;
	while (*s1 != '\0')
	{
		s = (char *)set;
		while (*s != '\0')
		{
			if (*s1 == *s)
			{
				s1++;
				i++;
				break ;
			}
			s++;
		}
		if (*s == '\0')
			break ;
	}
	return (i);
}

static size_t	f_trimend(char *s1, const char *set, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s1 = s1 + len - 1;
	while (*s1 != '\0')
	{
		s = (char *)set;
		while (*s != '\0')
		{
			if (*s1 == *s)
			{
				s1--;
				i++;
				break ;
			}
			s++;
		}
		if (*s == '\0')
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	char	*p;
	size_t	start;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	p = (char *)s1;
	start = f_trimstart(p, set);
	len = ft_strlen(s1);
	if (start == len)
		len = 0;
	else
		len = len - start - f_trimend(p, set, len);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (r)
		ft_strlcpy(r, p + start, len + 1);
	return (r);
}
