/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:36:23 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/07 00:20:07 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		len;
	char	*r;

	len = ft_numlen(n);
	r = (char *)malloc((len + 1) * sizeof(char));
	if (r)
	{
		r[len] = '\0';
		while (len-- > 0)
		{
			if (n >= 0)
				r[len] = (n % 10) + 48;
			else
				r[len] = (n % 10) * -1 + 48;
			n /= 10;
		}
		if (r[1] && r[0] == '0')
			r[0] = '-';
	}
	return (r);
}
