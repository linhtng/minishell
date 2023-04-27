/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:40:59 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/01 17:52:42 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*p1;
	void	*p2;

	size = ft_strlen(s);
	p1 = (char *)s;
	p2 = malloc((size + 1) * sizeof(char));
	if (p2)
		ft_memcpy(p2, s, size + 1);
	return (p2);
}
