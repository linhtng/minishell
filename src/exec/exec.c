/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:11:53 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/12 18:44:33 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	exec(t_cmd *cmd, t_list	**env_list, t_list *cmd_list)
{
	char	*cmd_path;
	char	**envp;
	pid_t	child_pid;

	child_pid = 0;
	if (cmd_is_builtin(cmd->pathname))
		child_pid = exec_builtin_child(cmd, env_list, cmd_list);
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
		child_pid = exec_path(cmd, cmd_path, envp, cmd_list);
		if (envp)
			free_env_array(envp);
		if (cmd_path)
			free(cmd_path);
	}
	return (child_pid);
}

static void	exec_cmd_list(t_list **env_list, t_list *cmd_list)
{
	t_cmd	*cmd;
	pid_t	*child_arr;
	int		i;

	i = 0;
	child_arr = (pid_t *)malloc(sizeof(int) * ft_lstsize(cmd_list));
	if (!child_arr)
	{
		print_error(1, "exec: error allocating memory for child PID array");
		g_exit_status = 1;
		return ;
	}
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (cmd->pathname)
			child_arr[i++] = exec(cmd, env_list, cmd_list);
		if (child_arr[i - 1] == -1)
			break ;
		close_redirects(&cmd->write_fd, &cmd->read_fd);
		cmd_list = cmd_list->next;
	}
	wait_children(child_arr, i);
	free(child_arr);
}

void	executor(t_list **env_list, t_list *cmd_list)
{
	t_cmd	*cmd;

	if (!cmd_list)
		return ;
	cmd = cmd_list->content;
	if (!cmd_list->next && cmd->pathname && cmd_is_builtin(cmd->pathname))
		g_exit_status = exec_builtin(cmd, env_list);
	else
		exec_cmd_list(env_list, cmd_list);
}
