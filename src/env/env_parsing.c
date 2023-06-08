/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:46:12 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/07 20:27:45 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parses single environment variable from a string in the form NAME[=value]
// returns malloced 2D array, or NULL in case of error
char	**parse_variable(char *str)
{
	int		nlen;
	char	**var;

	nlen = 0;
	var = (char **)malloc(2 * sizeof(char *));
	if (!var)
		return (NULL);
	while (str[nlen] != '\0' && str[nlen] != '=')
		nlen++;
	var[0] = ft_substr(str, 0, nlen);
	if (!var[0])
		free(var);
	if (!var[0])
		return (NULL);
	if (str[nlen] == '=')
	{
		var[1] = ft_substr(str, nlen + 1, ft_strlen(str) - nlen - 1);
		if (!var[1])
			free_envvar(var);
		if (!var[1])
			return (NULL);
	}
	else
		var[1] = NULL;
	return (var);
}

static void	get_shlvl(t_list **env_list)
{
	char	*shlvl;

	shlvl = get_envvar(env_list, "SHLVL");
	if (shlvl)
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		update_envvar(env_list, "SHLVL", shlvl);
		free(shlvl);
	}
	else
		update_envvar(env_list, "SHLVL", "1");
}

// parses environment from main's **envp argument into a linked list **env_list
// each environment variable is stored into malloced 2D array using ft_split
// does not parse $_ or $OLDPWD
void	parse_env(t_list **env_list, char **envp)
{
	char	**var;

	while (*envp)
	{
		var = parse_variable(*envp);
		if (!var)
		{
			clear_env_list(env_list);
			print_error(1, "Error while allocating memory for environment");
			exit(1);
		}
		if (!ft_strncmp(var[0], "_", 2) || !ft_strncmp(var[0], "OLDPWD", 7))
			free_envvar(var);
		else
		{
			if (!add_to_list(env_list, var))
			{
				clear_env_list(env_list);
				print_error(1, "Error while allocating memory for environment");
				exit(1);
			}
		}
		envp++;
	}
	get_shlvl(env_list);
}
