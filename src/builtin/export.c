/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:21:50 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/05 21:01:18 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_full_env(t_list *env_list)
{
	char	**envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
		if (envvar[1])
			printf("%s=%s\n", envvar[0], envvar[1]);
		else
			printf("%s\n", envvar[0]);
		if (env_list->next)
			print_full_env(env_list->next);
	}
}

static void	add_envvar(t_list **env_list, char **var)
{
	t_list	*var_node;

	var_node = find_envvar(env_list, var[0]);
	if (var[1])
	{
		if (var_node)
			del_envvar(env_list, var_node);
		ft_lstadd_back(env_list, ft_lstnew(var));
	}
	else
	{
		if (!var_node)
			ft_lstadd_back(env_list, ft_lstnew(var));
		else
			free_envvar(var);
	}
}

// export builtin
int	export(t_list **env_list, char **args)
{
	int		retval;
	char	**var;

	retval = 0;
	if (!*args)
		print_full_env(*env_list);
	while (*args)
	{
		var = parse_variable(*args);
		if (!var)
		{
			print_error(2, "export: ", "could not allocate memory");
			return (1);
		}
		if (check_envvar_name(var[0]))
			add_envvar(env_list, var);
		else
		{
			print_error(4, "export: ", *args, ": ", "not a valid identifier");
			free_envvar(var);
			retval = 1;
		}
		args++;
	}
	return (retval);
}
