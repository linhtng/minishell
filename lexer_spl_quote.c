/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_spl_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:50:11 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/17 16:51:06 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_with_quotes(char const *s, char const c, int quotes)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	quotes = 0;
	while (*s != '\0')
	{
		if (*s == c || quotes)
			i = 0;
		if ((*s == '\'' || *s == '\"') && quotes == 0)
		{
			quotes = 1;
			count++;
		}
		else if ((*s == '\'' || *s == '\"') && quotes == 1)
			quotes = 0;
		if (*s != c && *s != '\'' && *s != '\"' && i == 0 && quotes == 0)
		{
			count++;
			i = 1;
		}
		s++;
	}
	return (count);
}

char	**make_arr_quotes(char const*s, char c, int quotes)
{
	char	**res;
	int		len;

	if (!s)
		return (NULL);
	len = count_with_quotes(s, c, quotes);
	res = (char **) malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (res);
}

static int	get_substr_in_quotes(char **arr, char const *s, t_spldata *data)
{
	if ((s[data->i] == '\'' || s[data->i] == '\"') && data->start >= 0)
	{
		arr[data->j] = ft_substr(s, data->start + 1, data->i - data->start - 1);
		if (!arr[data->j])
			return (free_arr_spl(arr, data->j));
		data->j++;
		data->start = -1;
		data->in_quotes = 0;
	}
	return (1);
}

static int	get_substr_out_quotes(char **arr, char const *s, t_spldata *data)
{
	arr[data->j] = ft_substr(s, data->start, data->i - data->start);
	if (!arr[data->j])
		return (free_arr_spl(arr, data->j));
	data->j++;
	data->start = -1;
	return (1);
}

void	do_split_with_quotes(char **arr, char const *s, char c)
{
	t_spldata	data;

	ft_bzero(&data, sizeof(t_spldata));
	data.start = -1;
	data.slen = ft_strlen(s);
	while (data.i <= data.slen)
	{
		if (s[data.i] != '\0' && s[data.i] != c && data.start < 0)
		{
			data.start = data.i;
			if (s[data.i] == '\'' || s[data.i] == '\"')
				data.in_quotes = 1;
		}
		else if (data.in_quotes == 1)
		{
			if (!get_substr_in_quotes(arr, s, &data))
				return (perror("Malloc error"));
		}
		else if ((s[data.i] == c || data.i == data.slen) && data.start >= 0)
		{
			if (!get_substr_out_quotes(arr, s, &data))
				return (perror("Malloc error"));
		}
		data.i++;
	}
}
