/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:58:47 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/18 14:12:44 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	f_find_nl_pos(char *s, ssize_t len)
{
	char	*p;
	ssize_t	i;

	i = 0;
	p = (char *)s;
	while (p && *p != '\n' && i < len)
	{
		p++;
		i++;
	}
	if (i < len)
	{
		i++;
	}
	return (i);
}

static char	*f_append_buf(
	char *ret,
	t_gnl_buf *buf,
	ssize_t *ret_size,
	ssize_t *len
)
{
	char	*b;

	if (buf->overlap)
		b = buf->overlap;
	else
		b = buf->content;
	*len = f_find_nl_pos(b, buf->size);
	ret = ft_memjoin(ret, b, *ret_size, *len);
	if (ret)
	{
		*ret_size += *len;
		if (*len == buf->size)
			buf->overlap = NULL;
		else if (buf->overlap)
			buf->overlap += *len;
		else
			buf->overlap = &buf->content[*len];
		buf->size -= *len;
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	char				*ret;
	ssize_t				ret_size;
	ssize_t				len;
	static t_gnl_buf	buffers[OPEN_MAX];
	t_gnl_buf			*buf;

	ret_size = 0;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	buf = &buffers[fd];
	ret = f_append_buf(NULL, buf, &ret_size, &len);
	while (ret_size == 0 || (ret && ret[ret_size - 1] != '\n'))
	{
		buf->size = read(fd, buf->content, BUFFER_SIZE);
		if (buf->size == -1 || (buf->size == 0 && ret_size == 0))
			return (NULL);
		if (buf->size == 0)
			break ;
		ret = f_append_buf(ret, buf, &ret_size, &len);
	}
	if (ret)
		ret = ft_memjoin(ret, "", ret_size, 1);
	return (ret);
}
