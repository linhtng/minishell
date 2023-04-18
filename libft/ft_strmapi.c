/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:53:15 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/04 19:55:04 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*r;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (r)
	{
		while (i < len)
		{
			r[i] = f(i, s[i]);
			i++;
		}
		r[len] = '\0';
	}
	return (r);
}
