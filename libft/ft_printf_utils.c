/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:06:38 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/18 14:32:04 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_init_opts(t_opts *opts)
{
	opts->hash = 0;
	opts->space = 0;
	opts->plus = 0;
	opts->minus = 0;
	opts->zero = 0;
	opts->period = 0;
	opts->width = 0;
	opts->prec = 0;
}

t_buf	*f_init_conv_array(int size)
{
	t_buf	*conv;

	conv = (t_buf *)malloc(sizeof(t_buf) * size);
	while (conv && size-- > 0)
	{
		conv[size].data = NULL;
		conv[size].len = 0;
	}
	return (conv);
}

t_buf	f_make_char_buf(int len, char c)
{
	t_buf	buf;

	if (len > 0)
		buf.data = (char *)malloc(len * sizeof(char));
	if (buf.data)
		ft_memset(buf.data, c, len);
	buf.len = len;
	return (buf);
}

void	f_add_padding(t_opts *opts, const char *specif, t_buf **conv)
{
	int		len;
	int		padfield;
	char	padchar;

	len = (*conv)[1].len + (*conv)[2].len + (*conv)[3].len;
	if (opts->width > len)
	{
		padchar = ' ';
		padfield = 0;
		if (opts->minus)
			padfield = 4;
		else if (opts->zero && !(ft_strchr("diuxX", *specif) && opts->period))
		{
			padfield = 2;
			padchar = '0';
		}
		(*conv)[padfield] = f_make_char_buf(opts->width - len, padchar);
	}
}

int	f_write_conversion(t_buf *conv)
{
	int		i;
	int		len;
	ssize_t	wbyt;

	i = 0;
	len = 0;
	wbyt = 0;
	while (i < CONV_ARR_LEN)
	{
		if (conv[i].data)
		{
			len += conv[i].len;
			if (wbyt >= 0)
				wbyt += write(1, conv[i].data, conv[i].len);
			if (wbyt != len)
				wbyt = -1;
			free(conv[i].data);
		}
		else if (conv[i].len > 0)
			wbyt = -1;
		i++;
	}
	free(conv);
	return (wbyt);
}
