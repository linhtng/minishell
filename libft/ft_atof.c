/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:26:10 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/09 19:03:50 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	f_parse_value(const char *str, double *r, int *e)
{
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		*r = *r * 10.0 + (*str - 48);
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str != '\0' && *str >= '0' && *str <= '9')
		{
			*r = *r * 10.0 + (*str - 48);
			str++;
			*e = *e - 1;
		}
	}
}

double	ft_atof(const char *str)
{
	double	r;
	int		s;
	int		e;

	r = 0.0;
	e = 0;
	s = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	f_parse_value(str, &r, &e);
	while (*str && *str != 'e' && *str != 'E')
		str++;
	if (*str == 'e' || *str == 'E')
		e += ft_atoi(++str);
	while (e++ < 0)
		r /= 10.0;
	while (e-- > 1)
		r *= 10.0;
	if (r == 0.0)
		return (r);
	return (r * s);
}
