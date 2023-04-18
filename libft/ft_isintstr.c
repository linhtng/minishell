/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isintstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:44:29 by jhenriks          #+#    #+#             */
/*   Updated: 2023/02/15 18:17:11 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isintstr(char *str)
{
	int		ret;
	int		nbr;
	int		nlen;
	int		slen;
	char	*nbrstr;

	ret = 0;
	nbr = INT_MAX;
	if (!ft_isnumstr(str))
		return (0);
	if (*str == '-')
		nbr = INT_MIN;
	if (*str == '+')
		str++;
	nlen = ft_numlen(nbr);
	slen = ft_strlen(str);
	nbrstr = ft_itoa(nbr);
	if (slen < nlen)
		ret = 1;
	else if (slen > nlen)
		ret = 0;
	else if (ft_strncmp(str, nbrstr, slen) <= 0)
		ret = 1;
	free(nbrstr);
	return (ret);
}
