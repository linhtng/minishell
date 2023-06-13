/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:37:05 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/12 17:12:01 by jhenriks         ###   ########.fr       */
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

// first checks if the cmd is executable absolute or relative path
// then tries to find a command from $PATH, checks that it is executable
// returns the full path as string on success, otherwise returns NULL
char	*expand_path(t_list *env_list, char *cmd)
{
	char	**path_array;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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

void	wait_children(pid_t *child_arr, int size)
{
	int		status;
	int		i;

	i = 0;
	while (i < size)
	{
		if (child_arr[i])
			waitpid(child_arr[i], &status, 0);
		i++;
	}
	if (child_arr[i - 1])
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (!WIFSIGNALED(status))
			g_exit_status = status;
	}
}

void	close_all_redirects(t_cmd *curr_cmd, t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (cmd == curr_cmd)
		{
			cmd_list = cmd_list->next;
			continue ;
		}
		close(cmd->read_fd);
		cmd_list = cmd_list->next;
	}
}
