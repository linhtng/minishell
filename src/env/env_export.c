/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:58:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/31 17:44:47 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free array generated with env_list_to_array
void	free_env_array(char **envp)
{
	char	**ptr;

	if (envp)
	{
		ptr = envp;
		while (*ptr)
		{
			free(*ptr);
			ptr++;
		}
		free(envp);
	}
}

// convert env list to array to pass it to subprocesses via **envp argument
// NOTE: remember to free the list after subprocesses finish with free_env_array
char	**env_list_to_array(t_list *env_list)
{
	char	**envp;
	char	**envptr;
	char	**envvar;

	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (!envp)
		return (NULL);
	envptr = envp;
	while (env_list)
	{
		envvar = (char **)env_list->content;
		*envptr = ft_strmjoin(3, envvar[0], "=", envvar[1]);
		if (!*envptr)
		{
			free_env_array(envp);
			return (NULL);
		}
		env_list = env_list->next;
		envptr++;
	}
	*envptr = NULL;
	return (envp);
}
