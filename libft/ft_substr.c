/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:49:58 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/14 15:07:41 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	mlen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		mlen = ft_strlen(s);
	else
		mlen = len;
	r = (char *)malloc((mlen + 1) * sizeof(char));
	if (r)
		ft_strlcpy(r, (char *)s + start, len + 1);
	return (r);
}
