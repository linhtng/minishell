/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:28:49 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/13 16:45:46 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*dir;

	dir = get_curr_dir();
	if (dir)
		printf("%s\n", dir);
	else
		printf(".\n");
	free(dir);
	return (0);
}
