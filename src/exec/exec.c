/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:11:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/12 16:28:50 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, t_list	**env_list)
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

static pid_t	exec_builtin_child(t_cmd *cmd, t_list **env_list)
{
	pid_t	child;
	child = fork();
	if (child == 0)
	{
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit (1);
		else
			exit (run_builtin(env_list, cmd->pathname, cmd->argv));
	}
	return (child);
}

static pid_t	exec_path(t_cmd *cmd, char *cmd_path, char **envp)
{
	pid_t	child;
	child = fork();
	if (child == 0)
	{
		sigquit_child();
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit(1);
		if (execve(cmd_path, cmd->argv, envp) == -1)
			print_error(4, "exec: ", cmd->pathname, ": ", strerror(errno));
		exit(1);
	}
	return (child);
}

static pid_t	exec(t_cmd *cmd, t_list	**env_list)
{
	char	*cmd_path;
	char	**envp;
	pid_t	child_pid;

	envp = NULL;
	cmd_path = NULL;
	child_pid = 0;
	if (cmd_is_builtin(cmd->pathname))
		child_pid = exec_builtin_child(cmd, env_list);
	else if (ft_strlen(cmd->pathname) > 0 && !ft_isemptystr(cmd->pathname))
	{
		cmd_path = expand_path(*env_list, cmd->pathname);
		if (!cmd_path)
		{
			print_error(2, "command not found: ", cmd->pathname);
			g_exit_status = 127;
			return (child_pid);
		}
		envp = env_list_to_array(*env_list);
		setup_signals_child();
		child_pid = exec_path(cmd, cmd_path, envp);
		if (envp)
			free_env_array(envp);
		if (cmd_path)
			free(cmd_path);
	}
	return (child_pid);
}

void	executor(t_list	**env_list, t_list *cmd_list)
{
	t_cmd	*cmd;
	pid_t	*child_arr;
	int 	i;

	if (!cmd_list)
		return ;
	child_arr = (pid_t *)malloc(sizeof(int) * ft_lstsize(cmd_list));
	i = 0;
	cmd = cmd_list->content;
	if (!cmd_list->next && cmd->pathname && cmd_is_builtin(cmd->pathname))
		g_exit_status = exec_builtin(cmd, env_list);
	else
	{
		while (cmd_list)
		{
			cmd = cmd_list->content;
			if (cmd->pathname)
				child_arr[i] = exec(cmd, env_list);
			close_redirects(&cmd->write_fd, &cmd->read_fd);
			cmd_list = cmd_list->next;
			i++;
		}
		wait_children(child_arr, i);
	}
}
