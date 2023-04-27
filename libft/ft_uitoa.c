/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:27:24 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/07 00:28:56 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	int		len;
	char	*r;

	len = ft_unumlen(n);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (r)
	{
		r[len] = '\0';
		while (len-- > 0)
		{
			r[len] = (n % 10) + 48;
			n /= 10;
		}
	}
	return (r);
}
