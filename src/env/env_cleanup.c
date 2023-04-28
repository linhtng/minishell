/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:32:10 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/28 19:05:09 by jhenriks         ###   ########.fr       */
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

	lst = *env_list;
	while (lst)
	{
		free_envvar((char **)lst->content);
		free(lst);
		lst = lst->next;
	}
}
