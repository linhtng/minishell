/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:35:35 by jhenriks          #+#    #+#             */
/*   Updated: 2023/01/18 14:28:06 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV_ARR_LEN 5

# include <stdarg.h>
# include "libft.h"

typedef struct s_opts
{
	char	hash;
	char	space;
	char	plus;
	char	minus;
	char	zero;
	char	period;
	int		width;
	int		prec;
}			t_opts;

typedef struct s_buf
{
	char	*data;
	int		len;
}			t_buf;

void	f_convert_char(char c, t_buf **conv);
void	f_convert_str(char *s, t_opts *opts, t_buf **conv);
void	f_convert_int(int i, t_opts *opts, t_buf **conv);
void	f_convert_uint(unsigned int u, t_opts *opts, t_buf **conv);
void	f_convert_hex(size_t x, t_opts *opts, const char specif, t_buf **conv);
void	f_init_opts(t_opts *opts);
t_buf	*f_init_conv_array(int size);
t_buf	f_make_char_buf(int len, char c);
void	f_add_padding(t_opts *opts, const char *specif, t_buf **conv);
int		f_write_conversion(t_buf *conv);

#endif
