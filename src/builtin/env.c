/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:16:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/02 20:18:54 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list *env_list)
{
	char	**envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
		if (envvar[1])
			ft_printf("%s=%s\n", envvar[0], envvar[1]);
		if (env_list->next)
			env(env_list->next);
	}
	return (0);
}
