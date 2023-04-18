/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:11:47 by jhenriks          #+#    #+#             */
/*   Updated: 2022/11/16 21:10:47 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	f_numfields(const char *s, char c)
{
	char	*p;
	size_t	i;

	p = (char *)s;
	i = 0;
	while (*p != '\0')
	{
		if (*p != c)
		{
			p++;
			if (*p == c || *p == '\0')
				i++;
		}
		else
			p++;
	}
	return (i);
}

static void	f_free_array(char **r, unsigned int n)
{
	while (n-- > 0)
		free(r[n]);
	free(r);
}

static char	**f_fill_array(char **r, char const *s, char c, unsigned int f)
{
	unsigned int	len;
	unsigned int	start;
	unsigned int	i;

	start = 0;
	i = 0;
	while (i < f)
	{
		if (s[start] != c)
		{
			len = 0;
			while (s[start + len] != c && s[start + len] != '\0')
				len++;
			r[i] = ft_substr(s, start, len);
			if (r[i] == NULL)
				f_free_array(r, i);
			if (r[i] == NULL)
				return (NULL);
			i++;
			start = start + len - 1;
		}
		start++;
	}
	r[i] = NULL;
	return (r);
}

char	**ft_split(char const *s, char c)
{
	char			**r;
	unsigned int	fields;

	if (!s)
		return (NULL);
	fields = f_numfields(s, c);
	r = (char **)malloc((fields + 1) * sizeof(char *));
	if (r)
		r = f_fill_array(r, s, c, fields);
	return (r);
}
