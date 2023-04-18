/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:14:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/02/16 22:55:13 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_intdup(void *n)
{
	int	*dupp;

	dupp = (int *)malloc(sizeof(int *));
	if (dupp)
		ft_memcpy(dupp, n, sizeof(int));
	return (dupp);
}
