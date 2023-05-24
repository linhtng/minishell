/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:39:03 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/02 20:40:55 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_list **env_list, char **args)
{
	int		retval;
	t_list	*var_node;

	retval = 0;
	while (env_list && *env_list && *args)
	{
		if (!check_envvar_name(*args))
		{
			print_error(4, "unset: ", *args, ": ", "not a valid identifier");
			retval = 1;
			args++;
			continue ;
		}
		var_node = find_envvar(env_list, *args);
		if (var_node)
			del_envvar(env_list, var_node);
		args++;
	}
	return (retval);
}
