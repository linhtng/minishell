/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isemptystr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:00:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/01 16:03:16 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isemptystr(const char *s)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '\0')
		return (1);
	else
		return (0);
}
