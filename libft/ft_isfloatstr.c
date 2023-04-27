/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloatstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:27:31 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/09 19:03:02 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isfloatstr(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '\0')
		return (1);
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
			str++;
		if (*str == '\0')
			return (1);
	}
	if (*str == 'e' || *str == 'E')
	{
		str++;
		if (*str == '-')
			str++;
		while (ft_isdigit(*str))
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}
