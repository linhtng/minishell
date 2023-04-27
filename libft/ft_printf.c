/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:47:29 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/12 13:17:01 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	f_parse_num_opts(const char *format, int *num)
{
	int		len;

	len = 0;
	*num = ft_atoi(format);
	while (*format >= '0' && *format <= '9')
	{
		len++;
		format++;
	}
	return (len);
}

static int	f_parse_opt_flags(const char *format, t_opts *opts)
{
	if (*format == '#')
		opts->hash = 1;
	else if (*format == ' ')
	{
		if (!opts->plus)
			opts->space = 1;
	}
	else if (*format == '+')
	{
		opts->space = 0;
		opts->plus = 1;
	}
	else if (*format == '-')
	{
		opts->zero = 0;
		opts->minus = 1;
	}
	else if (*format == '0')
	{
		if (!opts->minus)
			opts->zero = 1;
	}
	else if (*format == '.')
		opts->period = 1;
	return (1);
}

static int	f_parse_opts(const char *format, t_opts *opts)
{
	int	opts_len;

	opts_len = 0;
	if (*format != '\0' && ft_strchr("# +-0", *format))
		opts_len += f_parse_opt_flags(format, opts);
	else if (*format == '.')
	{
		opts_len += f_parse_opt_flags(format, opts);
		opts_len += f_parse_num_opts(format + 1, &(opts->prec));
	}
	else if (*format > '0' && *format <= '9')
		opts_len += f_parse_num_opts(format, &(opts->width));
	else
		return (0);
	opts_len += f_parse_opts(format + opts_len, opts);
	return (opts_len);
}

static int	f_convert_args(const char *specif, va_list args, t_opts *opts)
{
	t_buf	*conv;

	conv = f_init_conv_array(CONV_ARR_LEN);
	if (!conv)
		return (-1);
	if (*specif == '\0')
		return (0);
	if (*specif == 'c')
		f_convert_char((char)va_arg(args, int), &conv);
	else if (*specif == 's')
		f_convert_str(va_arg(args, char *), opts, &conv);
	else if (*specif == 'p')
		f_convert_hex(va_arg(args, size_t), opts, *specif, &conv);
	else if (*specif == 'd' || *specif == 'i')
		f_convert_int(va_arg(args, int), opts, &conv);
	else if (*specif == 'u')
		f_convert_uint(va_arg(args, unsigned int), opts, &conv);
	else if (*specif == 'x' || *specif == 'X')
		f_convert_hex(va_arg(args, unsigned int), opts, *specif, &conv);
	else if (*specif == '%')
		f_convert_char('%', &conv);
	else
		f_convert_char(*specif, &conv);
	f_add_padding(opts, specif, &conv);
	return (f_write_conversion(conv));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_opts	opts;
	int		len;
	ssize_t	wbyt;

	va_start(args, format);
	len = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			f_init_opts(&opts);
			format += f_parse_opts(format + 1, &opts) + 1;
			wbyt = f_convert_args(format, args, &opts);
		}
		else
			wbyt = write(1, format, 1);
		if (wbyt < 0)
			return (-1);
		len += wbyt;
		if (*format != '\0')
			format++;
	}
	va_end(args);
	return (len);
}
