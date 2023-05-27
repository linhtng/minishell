/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:11:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/27 17:57:52 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, t_list	*env_list)
{
	if (!redirect_streams(cmd->write_fd, cmd->read_fd))
		exit(1);
	else
		exit(run_builtin(env_list, cmd->pathname, cmd->argv));
}

static int	exec_path(t_cmd *cmd, char *cmd_path, char **envp)
{
	if (!redirect_streams(cmd->write_fd, cmd->read_fd))
		exit(1);
	if (execve(cmd_path, cmd->argv, envp) == -1)
		print_error(4, "exec error: ", cmd->pathname, ": ", strerror(errno));
	exit(1);
}

static int	exec(t_cmd *cmd, t_list	*env_list, char **cmd_path, char ***envp)
{
	pid_t	child;
	int		status;

	if (cmd_is_builtin(cmd->pathname))
	{
		child = fork();
		if (child == 0)
			exec_builtin(cmd, env_list);
	}
	else
	{
		*cmd_path = expand_path(env_list, cmd->pathname);
		if (!*cmd_path)
			print_error(2, "command not found: ", cmd->pathname);
		if (!*cmd_path)
			return (127);
		*envp = env_list_to_array(env_list);
		child = fork();
		if (child == 0)
			exec_path(cmd, *cmd_path, *envp);
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

void	executor(t_list	*env_list, t_list *cmd_list)
{
	t_cmd	*cmd;
	char	*cmd_path;
	char	**envp;

	while (cmd_list)
	{
		cmd = cmd_list->content;
		envp = NULL;
		cmd_path = NULL;
		g_exit_status = exec(cmd, env_list, &cmd_path, &envp);
		close_redirects(&cmd->write_fd, &cmd->read_fd);
		if (envp)
			free_env_array(envp);
		if (cmd_path)
			free(cmd_path);
		cmd_list = cmd_list->next;
	}
}
