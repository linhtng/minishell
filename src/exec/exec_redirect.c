/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:39:40 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/03 18:40:51 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close files opened for redirections, and reset the fd variables
void	close_redirects(int *write_fd, int *read_fd)
{
	if (*write_fd != 0 && *write_fd != STDOUT_FILENO)
	{
		close(*write_fd);
		*write_fd = STDOUT_FILENO;
	}
	if (*read_fd != 0 && *read_fd != STDIN_FILENO)
	{
		close(*read_fd);
		*read_fd = STDIN_FILENO;
	}
}

// redirect standard streams from/to file descriptors
int	redirect_streams(int write_fd, int read_fd)
{
	int	wfd;
	int	rfd;

	wfd = 0;
	rfd = 0;
	if (write_fd != STDOUT_FILENO)
		wfd = dup2(write_fd, STDOUT_FILENO);
	if (read_fd != STDIN_FILENO)
		rfd = dup2(read_fd, STDIN_FILENO);
	if (wfd == -1 || rfd == -1)
	{
		close_redirects(&write_fd, &read_fd);
		print_error(2, "redirection error: ", strerror(errno));
		return (0);
	}
	return (1);
}
