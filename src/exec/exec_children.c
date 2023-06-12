/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:08:51 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/12 17:22:58 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_list	**env_list)
{
	int	ret;
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (stdin == -1 || stdout == -1)
	{
		print_error(2, "dup error: ", strerror(errno));
		return (1);
	}
	if (!redirect_streams(cmd->write_fd, cmd->read_fd))
		ret = 1;
	else
		ret = run_builtin(env_list, cmd->pathname, cmd->argv);
	if (dup2(stdin, STDIN_FILENO) == -1 || dup2(stdout, STDOUT_FILENO) == -1)
	{
		print_error(2, "dup2 error: ", strerror(errno));
		ret = 1;
	}
	close(stdin);
	close(stdout);
	return (ret);
}

pid_t	exec_builtin_child(t_cmd *cmd, t_list **env_list, t_list *cmd_list)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		close_all_redirects(cmd, cmd_list);
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit (1);
		else
			exit (run_builtin(env_list, cmd->pathname, cmd->argv));
	}
	if (child == -1)
		print_error(5, "exec: ", "error forking child process",
			cmd->pathname, ": ", strerror(errno));
	return (child);
}

pid_t	exec_path(t_cmd *cmd, char *cmd_path, char **envp, t_list *cmd_list)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		sigquit_child();
		close_all_redirects(cmd, cmd_list);
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit(1);
		if (execve(cmd_path, cmd->argv, envp) == -1)
			print_error(4, "exec: ", cmd->pathname, ": ", strerror(errno));
		exit(1);
	}
	if (child == -1)
		print_error(5, "exec: ", "error forking child process",
			cmd->pathname, ": ", strerror(errno));
	return (child);
}
