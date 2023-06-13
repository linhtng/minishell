/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:37:05 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/13 20:45:12 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_is_builtin(char *path)
{
	if (!path)
		return (0);
	if (!ft_strncmp("cd", path, 3)
		|| !ft_strncmp("echo", path, 5)
		|| !ft_strncmp("env", path, 4)
		|| !ft_strncmp("exit", path, 5)
		|| !ft_strncmp("export", path, 7)
		|| !ft_strncmp("pwd", path, 4)
		|| !ft_strncmp("unset", path, 6))
		return (1);
	else
		return (0);
}

// executes builtin based on path and returns its status value
// returns -1 if path is not a builtin command
int	run_builtin(t_list	**env_list, char *path, char **argv)
{
	int	status;

	if (!ft_strncmp("cd", path, 3))
		status = cd(env_list, argv[1]);
	else if (!ft_strncmp("echo", path, 5))
		status = echo(argv + 1);
	else if (!ft_strncmp("env", path, 4))
		status = env(*env_list, argv + 1);
	else if (!ft_strncmp("exit", path, 5))
		status = exit_shell(env_list, argv + 1);
	else if (!ft_strncmp("export", path, 7))
		status = export(env_list, argv + 1);
	else if (!ft_strncmp("pwd", path, 4))
		status = pwd();
	else if (!ft_strncmp("unset", path, 6))
		status = unset(env_list, argv + 1);
	else
		status = 1;
	return (status);
}

static char	*cmd_from_path(t_list *env_list, char *cmd)
{
	char	**path_array;
	char	*path;
	int		i;

	path_array = ft_split(get_envvar(&env_list, "PATH"), ':');
	path = NULL;
	i = 0;
	while (path_array && path_array[i])
	{
		path = ft_strmjoin(3, path_array[i], "/", cmd);
		if (!path || (access(path, F_OK) == 0 && access(path, X_OK) == 0))
			break ;
		free(path);
		path = NULL;
		i++;
	}
	i = 0;
	while (path_array && path_array[i])
		free(path_array[i++]);
	if (path_array)
		free(path_array);
	return (path);
}

static void	cmd_error(int status, char *cmd)
{
	if (status == 126)
	{
		print_error(2, "permission denied: ", cmd);
		g_exit_status = 126;
	}
	else if (status == 127)
	{
		print_error(2, "command not found: ", cmd);
		g_exit_status = 127;
	}
}

// first checks if the cmd is executable absolute or relative path
// then tries to find a command from $PATH, checks that it is executable
// returns the full path as string on success, otherwise returns NULL
char	*expand_path(t_list *env_list, char *cmd)
{
	char	*path;

	if (ft_strlen(cmd) == 0 || ft_strncmp(cmd, "..", 3) == 0
		|| ft_strncmp(cmd, ".", 2) == 0)
		path = NULL;
	else if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (ft_strdup(cmd));
			else
			{
				cmd_error(126, cmd);
				return (NULL);
			}
		}
		else
			path = NULL;
	}
	else
		path = cmd_from_path(env_list, cmd);
	if (!path)
		cmd_error(127, cmd);
	return (path);
}
