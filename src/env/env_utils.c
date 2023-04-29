/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:26:47 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/29 20:37:59 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper to find env variable with name *var from **env_list
// returns pointer to the variable's list node if one is found
// otherwise returns NULL
t_list	*find_envvar(t_list **env_list, char *var)
{
	t_list	*lst;
	char	**envvar;

	if (!env_list || !*env_list)
		return (NULL);
	lst = *env_list;
	envvar = (char **)lst->content;
	while (lst && ft_strncmp(envvar[0], var, ft_strlen(var) + 1))
	{
		lst = lst->next;
		if (lst)
			envvar = (char **)lst->content;
	}
	return (lst);
}

// getenv() replacement
char	*get_envvar(t_list **env_list, char *var)
{
	char	**envvar;

	envvar = (char **)find_envvar(env_list, var)->content;
	return (envvar[1]);
}

// update env variable 'name' with 'value'
// if variable does not exit in the environment, it will be added
// returns 0 on failure, 1 otherwise
int	update_envvar(t_list **env_list, char *name, char *value)
{
	char	**var;
	t_list	*var_node;

	if (!env_list || !name || !value)
		return (0);
	var = (char **)malloc(2 * sizeof(char *));
	if (!var)
		return (0);
	var[0] = ft_strdup(name);
	var[1] = ft_strdup(value);
	if (!var[0] || !var[1])
	{
		free_envvar(var);
		return (0);
	}
	var_node = find_envvar(env_list, var[0]);
	if (var_node)
		del_envvar(env_list, var_node);
	ft_lstadd_back(env_list, ft_lstnew(var));
	return (1);
}
