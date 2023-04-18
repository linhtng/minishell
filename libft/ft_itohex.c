/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:41:05 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/07 00:45:22 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itohex(size_t n, int caps)
{
	int		len;
	char	*ret;
	int		tmp;

	len = ft_hexlen(n);
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret)
	{
		ret[len] = '\0';
		len--;
		while (len >= 0)
		{
			tmp = n % 16;
			if (tmp <= 9)
				ret[len] = tmp + '0';
			else if (caps)
				ret[len] = tmp + 'A' - 10;
			else
				ret[len] = tmp + 'a' - 10;
			n = n / 16;
			len--;
		}
	}
	return (ret);
}
