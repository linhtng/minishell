/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:46:42 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/10 15:42:52 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	r;
	int		s;

	r = 0;
	s = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			break ;
		r *= 10;
		r += (*str - 48);
		str++;
		if (r < 0 && s > 0)
			return (-1);
		else if (r < 0 && s < 0)
			return (0);
	}
	return (r * s);
}
