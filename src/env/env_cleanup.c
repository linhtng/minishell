/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:32:10 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/30 19:58:53 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// frees single environment variable 2D array
void	free_envvar(char **var)
{
	if (var[0])
		free(var[0]);
	if (var[1])
		free(var[1]);
	if (var)
		free(var);
}

// clears the whole environment variable list
void	clear_env_list(t_list **env_list)
{
	t_list	*lst;

	if (!env_list)
		return ;
	lst = *env_list;
	while (lst)
	{
		free_envvar((char **)lst->content);
		free(lst);
		lst = lst->next;
	}
}

// helper to delete environment variable from the list
void	del_envvar(t_list **env_list, t_list *var_node)
{
	t_list	*lst;
	t_list	*prev;

	lst = *env_list;
	prev = NULL;
	while (lst)
	{
		if (lst == var_node)
		{
			if (prev)
				prev->next = lst->next;
			else
				*env_list = (*env_list)->next;
			free_envvar((char **)var_node->content);
			free(var_node);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}
