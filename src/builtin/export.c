/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:21:50 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/02 20:24:50 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export builtin
// TODO print_full_env if no arguments given???
int	export(t_list **env_list, char **args)
{
	int		retval;
	char	**var;
	t_list	*var_node;

	retval = 0;
	while (env_list && *env_list && *args)
	{
		var = parse_variable(*args);
		if (!var)
			return (1);
		if (!check_envvar_name(var[0]))
		{
			print_error(4, "export: ", *args, ": ", "not a valid identifier");
			args++;
			retval = 1;
			continue ;
		}
		var_node = find_envvar(env_list, var[0]);
		if (var_node && var[1])
			del_envvar(env_list, var_node);
		if (!var_node || (var_node && var[1]))
			ft_lstadd_back(env_list, ft_lstnew(var));
		args++;
	}
	return (retval);
}
