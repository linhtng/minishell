/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:28:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/13 15:38:20 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_dir(t_list **env_list, char *path)
{
	char	*old_path;
	char	*curr_path;

	if (ft_strlen(path) == 0)
		return (1);
	old_path = get_curr_dir();
	if (access(path, F_OK) < 0)
		print_error(2, "cd: no such file or directory: ", path);
	else if (access(path, X_OK) < 0)
		print_error(2, "cd: permission denied: ", path);
	else if (!ft_is_dir(path))
		print_error(2, "cd: not a directory: ", path);
	else if (chdir(path) == 0)
	{
		curr_path = get_curr_dir();
		update_envvar(env_list, "OLDPWD", old_path);
		update_envvar(env_list, "PWD", curr_path);
		free(old_path);
		free(curr_path);
		return (1);
	}
	else
		print_error(2, "cd: could not change directory: ", path);
	free(old_path);
	return (0);
}

// cd builtin, takes relative or absolute path as an argument
// if no argument is given, attempts to change cwd to $HOME
int	cd(t_list **env_list, char *path)
{
	char	*home_dir;

	if (path)
	{
		if (change_dir(env_list, path))
			return (0);
	}
	else
	{
		home_dir = get_envvar(env_list, "HOME");
		if (home_dir)
		{
			if (change_dir(env_list, home_dir))
				return (0);
		}
		else
			print_error(1, "cd: HOME not set");
	}
	return (1);
}
