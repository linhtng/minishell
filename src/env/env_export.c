/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:58:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/15 15:13:31 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free array generated with env_list_to_array
void	free_env_array(char **envp)
{
	char	**ptr;

	ptr = envp;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(envp);
}

// convert env list to array to pass it to subprocesses via **envp argument
// NOTE: remember to free the list after subprocesses finish with free_env_array
char	**env_list_to_array(t_list *env_list)
{
	char	**envp;
	char	**envptr;
	char	**envvar;
	size_t	len;

	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (!envp)
		return (NULL);
	envptr = envp;
	while (env_list)
	{
		envvar = (char **)env_list->content;
		len = ft_strlen(envvar[0]) + ft_strlen(envvar[1]) + 2;
		*envptr = (char *)malloc(sizeof(char) * len);
		if (!*envptr)
			free_env_array(envp);
		if (!*envptr)
			return (NULL);
		ft_strlcat(*envptr, envvar[0], len);
		ft_strlcat(*envptr, "=", len);
		ft_strlcat(*envptr, envvar[1], len);
		env_list = env_list->next;
		envptr++;
	}
	*envptr = NULL;
	return (envp);
}
