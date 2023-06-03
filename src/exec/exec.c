/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:11:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/03 21:42:49 by jhenriks         ###   ########.fr       */
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

static void	exec_builtin_child(t_cmd *cmd, t_list **env_list,
	t_list **child_list)
{
	pid_t	child;
	pid_t	*childptr;

	child = fork();
	if (child == 0)
	{
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit (1);
		else
			exit (run_builtin(env_list, cmd->pathname, cmd->argv));
	}
	childptr = (pid_t *) malloc(sizeof(pid_t));
	*childptr = child;
	ft_lstadd_back(child_list, ft_lstnew(childptr));
}

static void	exec_path(t_cmd *cmd, char *cmd_path, char **envp,
	t_list **child_list)
{
	pid_t	child;
	pid_t	*childptr;

	child = fork();
	if (child == 0)
	{
		sigquit_child();
		if (!redirect_streams(cmd->write_fd, cmd->read_fd))
			exit(1);
		if (execve(cmd_path, cmd->argv, envp) == -1)
			print_error(4, "exec error:", cmd->pathname, ": ", strerror(errno));
		exit(1);
	}
	childptr = (pid_t *) malloc(sizeof(pid_t));
	*childptr = child;
	ft_lstadd_back(child_list, ft_lstnew(childptr));
}

static void	exec(t_cmd *cmd, t_list	**env_list, t_list **child_list)
{
	char	*cmd_path;
	char	**envp;

	envp = NULL;
	cmd_path = NULL;
	if (cmd_is_builtin(cmd->pathname))
		exec_builtin_child(cmd, env_list, child_list);
	else if (ft_strlen(cmd->pathname) > 0 && !ft_isemptystr(cmd->pathname))
	{
		cmd_path = expand_path(*env_list, cmd->pathname);
		if (!cmd_path)
		{
			print_error(2, "command not found: ", cmd->pathname);
			g_exit_status = 127;
			return ;
		}
		envp = env_list_to_array(*env_list);
		setup_signals_child();
		exec_path(cmd, cmd_path, envp, child_list);
		if (envp)
			free_env_array(envp);
		if (cmd_path)
			free(cmd_path);
	}
}

void	executor(t_list	**env_list, t_list *cmd_list)
{
	t_cmd	*cmd;
	t_list	*child_list;

	if (!cmd_list)
		return ;
	child_list = NULL;
	cmd = cmd_list->content;
	if (!cmd->pathname)
		return ;
	if (!cmd_list->next && cmd_is_builtin(cmd->pathname))
		g_exit_status = exec_builtin(cmd, env_list);
	else
	{
		while (cmd_list)
		{
			cmd = cmd_list->content;
			exec(cmd, env_list, &child_list);
			close_redirects(&cmd->write_fd, &cmd->read_fd);
			cmd_list = cmd_list->next;
		}
		wait_children(child_list);
		ft_lstclear(&child_list, free);
	}
}
