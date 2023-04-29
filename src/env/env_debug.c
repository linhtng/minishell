/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:12:51 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/29 21:17:17 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print full environment, including variables with no values
int	print_full_env(t_list *env_list)
{
	char	**envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
		if (envvar[1])
			ft_printf("%s=%s\n", envvar[0], envvar[1]);
		else
			ft_printf("%s\n", envvar[0]);
		if (env_list->next)
			print_full_env(env_list->next);
	}
	return (0);
}
