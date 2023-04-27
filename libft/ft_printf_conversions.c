/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 09:03:42 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/12 13:45:34 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	f_convert_char(char c, t_buf **conv)
{
	(*conv)[3] = f_make_char_buf(1, c);
}

void	f_convert_str(char *s, t_opts *opts, t_buf **conv)
{
	if (!s)
		s = "(null)";
	(*conv)[3].len = (ft_strlen(s));
	if (opts->period && opts->prec < (*conv)[3].len)
		(*conv)[3].len = opts->prec;
	(*conv)[3].data = ft_substr(s, 0, (*conv)[3].len);
}

void	f_convert_int(int i, t_opts *opts, t_buf **conv)
{
	char	*tmp;

	if (i >= 0 && !(i == 0 && opts->period))
	{
		(*conv)[3].len = ft_numlen(i);
		(*conv)[3].data = ft_itoa(i);
		if (opts->plus)
			(*conv)[1] = f_make_char_buf(1, '+');
		else if (opts->space)
			(*conv)[1] = f_make_char_buf(1, ' ');
	}
	else if (i < 0)
	{
		(*conv)[3].len = ft_numlen(i) - 1;
		tmp = ft_itoa(i);
		(*conv)[3].data = ft_substr(tmp, 1, (*conv)[3].len);
		if (tmp)
			free(tmp);
		(*conv)[1] = f_make_char_buf(1, '-');
	}
	if (opts->period && opts->prec > (*conv)[3].len)
		(*conv)[2] = f_make_char_buf(opts->prec - (*conv)[3].len, '0');
}

void	f_convert_uint(unsigned int u, t_opts *opts, t_buf **conv)
{
	if (!(u == 0 && opts->period))
	{
		(*conv)[3].len = ft_unumlen(u);
		(*conv)[3].data = ft_uitoa(u);
	}
	if (opts->period && opts->prec > (*conv)[3].len)
		(*conv)[2] = f_make_char_buf(opts->prec - (*conv)[3].len, '0');
}

void	f_convert_hex(size_t x, t_opts *opts, const char specif, t_buf **conv)
{
	int	caps;

	if (specif == 'X')
		caps = 1;
	else
		caps = 0;
	if (!(x == 0 && opts->period))
	{
		(*conv)[3].len = ft_hexlen(x);
		(*conv)[3].data = ft_itohex(x, caps);
	}
	if (specif == 'p' || (opts->hash && x != 0))
	{
		(*conv)[1].len = 2;
		if (caps)
			(*conv)[1].data = ft_substr("0X", 0, 2);
		else
			(*conv)[1].data = ft_substr("0x", 0, 2);
	}
	if (opts->period && opts->prec > (*conv)[3].len)
		(*conv)[2] = f_make_char_buf(opts->prec - (*conv)[3].len, '0');
}
