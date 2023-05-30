/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:11:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/30 17:00:02 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(t_cmd *cmd, t_list	*env_list)
{
	int	ret;
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (!redirect_streams(cmd->write_fd, cmd->read_fd))
		ret = 1;
	else
		ret = run_builtin(env_list, cmd->pathname, cmd->argv);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (ret);
}

static void	exec_builtin_child(t_cmd *cmd, t_list	*env_list)
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
	waitpid(child, &g_exit_status, 0);
}

static void	exec_path(t_cmd *cmd, char *cmd_path, char **envp)
{
	int		status;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		sigquit_child();
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit(1);
		if (execve(cmd_path, cmd->argv, envp) == -1)
			print_error(4, "exec error:",
				cmd->pathname, ": ", strerror(errno));
		exit(1);
	}
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

static void	exec(t_cmd *cmd, t_list	*env_list, char **cmd_path, char ***envp)
{
	if (cmd_is_builtin(cmd->pathname))
		exec_builtin_child(cmd, env_list);
	else
	{
		*cmd_path = expand_path(env_list, cmd->pathname);
		if (!*cmd_path)
		{
			print_error(2, "command not found: ", cmd->pathname);
			g_exit_status = 127;
			return ;
		}
		*envp = env_list_to_array(env_list);
		setup_signals_child();
		exec_path(cmd, *cmd_path, *envp);
	}
}

void	executor(t_list	*env_list, t_list *cmd_list)
{
	t_cmd	*cmd;
	char	*cmd_path;
	char	**envp;

	cmd = cmd_list->content;
	if (!cmd_list->next && cmd_is_builtin(cmd->pathname))
		g_exit_status = exec_builtin(cmd, env_list);
	else
	{
		while (cmd_list)
		{
			cmd = cmd_list->content;
			envp = NULL;
			cmd_path = NULL;
			exec(cmd, env_list, &cmd_path, &envp);
			close_redirects(&cmd->write_fd, &cmd->read_fd);
			if (envp)
				free_env_array(envp);
			if (cmd_path)
				free(cmd_path);
			cmd_list = cmd_list->next;
		}
	}
}
