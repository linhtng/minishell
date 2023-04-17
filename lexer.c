/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:36:51 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/17 19:42:10 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_count(char const *s, char const c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
			i = 0;
		if (*s != c && i == 0)
		{
			count++;
			i = 1;
		}
		s++;
	}
	return (count);
}

char	**make_arr(char const*s, char c)
{
	char	**res;
	int		len;

	if (!s)
		return (NULL);
	len = word_count(s, c);
	res = (char **) malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = NULL;
	return (res);
}

int	free_arr_spl(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		arr[i] = NULL;
		free(arr[i]);
		i++;
	}
	arr = NULL;
	free(arr);
	return (0);
}

static int	do_split(char **arr, char const *s, char c)
{
	size_t		i;
	int			j;
	int			word_start;
	size_t		slen;

	i = 0;
	j = 0;
	word_start = -1;
	slen = ft_strlen(s);
	while (i <= slen)
	{
		if (s[i] != '\0' && s[i] != c && word_start < 0)
			word_start = i;
		if ((s[i] == c || i == slen) && word_start >= 0)
		{
			arr[j] = ft_substr(s, word_start, i - word_start);
			if (!arr[j])
				return (free_arr_spl(arr, j));
			j++;
			word_start = -1;
		}
		i++;
	}
	return (j);
}

char	**token_split(char const *s, char c)
{
	char	**arr;
	int		in_quotes;
	int		in_dquotes;

	in_quotes = count_occurences(s, '\'');
	in_dquotes = count_occurences(s, '\"');
	if ((in_quotes && in_quotes % 2 == 0) || \
			(in_dquotes && in_dquotes % 2 == 0))
	{
		arr = make_arr_quotes(s, c, in_quotes);
		if (!arr)
			return (NULL);
		do_split_with_quotes(arr, s, c);
	}
	else
	{
		arr = make_arr(s, c);
		if (!arr)
			return (NULL);
		do_split(arr, s, c);
	}
	return (arr);
}

/* int main(int arc, char **arv)
{
    char    **tokens;

    tokens = NULL;
	printf("%d\n", arc);
    if (arc == 2)
    {
        tokens = lexer(arv[1]);
        print_arr(tokens);
    }
    return (0);
} */
