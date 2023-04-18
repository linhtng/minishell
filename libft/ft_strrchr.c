/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:51:35 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/14 15:42:29 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	char	*l;

	p = (char *)s;
	l = NULL;
	while (*p != '\0')
	{
		if (*p == (char)c)
			l = p;
		p++;
	}
	if (l == NULL && c == '\0')
		return (p);
	else if (l != NULL)
		return (l);
	else
		return (NULL);
}
