/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:28:35 by jhenriks          #+#    #+#             */
/*   Updated: 2023/06/13 16:33:26 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// helper function for getting current absolute directory path
// returns pointer to the path as string, or NULL in case of error
// the returned path doesn't have the ending forward slash
char	*get_curr_dir(void)
{
	char	*buf;
	char	*dir;

	buf = NULL;
	dir = NULL;
	buf = (char *)malloc(PATH_MAX);
	if (buf)
	{
		dir = getcwd(buf, PATH_MAX);
		if (dir)
			dir = ft_strdup(dir);
		free(buf);
	}
	return (dir);
}

// helper that checks whether the path is a directory
// could be useful add to libft?
int	ft_is_dir(const char *path)
{
	struct stat	stat_buf;

	if (stat(path, &stat_buf) != 0)
		return (0);
	return (S_ISDIR(stat_buf.st_mode));
}
