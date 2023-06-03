/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:16:19 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/03 21:32:42 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_list *env_list, char **args)
{
	char	**envvar;

	if (*args)
	{
		print_error(2, "env: ", "too many arguments");
		return (1);
	}
	if (env_list)
	{
		envvar = (char **)env_list->content;
		if (envvar[1])
			printf("%s=%s\n", envvar[0], envvar[1]);
		if (env_list->next)
			env(env_list->next, args);
	}
	return (0);
}
