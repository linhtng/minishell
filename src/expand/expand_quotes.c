/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:58:06 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/15 17:37:41 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	between_quotes(char *string, int index)
{
	int	q_status;

	q_status = var_quote_status(string, index, N_QUOTE);
	if ((string[index] == '\'' || string[index] == '\"') && q_status == N_QUOTE)
		return (0);
	if ((string[index] == '\'' && q_status == IN_SQUOTE)
		|| (string[index] == '\"' && q_status == IN_DQUOTE))
		return (0);
	return (1);
}

void	skip_quotes(char *string, int *index)
{
	while ((string[*index] == '\'' || string[*index] == '\"')
		&& !between_quotes(string, *index))
		(*index)++;
}

int	removed_quote(t_token *token, int len)
{
	char	*new_str;
	int		i;
	int		j;

	if (len)
	{
		new_str = (char *) malloc(sizeof(char) * (len + 1));
		if (!new_str)
			return (0);
		ft_bzero(new_str, len + 1);
		token->len = len;
		i = 0;
		j = 0;
		while (len--)
		{
			skip_quotes(token->string, &i);
			new_str[j++] = token->string[i++];
		}
	}
	else
		new_str = ft_strdup("");
	free(token->string);
	token->string = new_str;
	return (1);
}

int	apply_quoting_rules(t_token *token)
{
	int		i;
	int		len;

	i = 0;
	if (!token->string)
		return (1);
	if (!ft_strchr(token->string, '\'') && !ft_strchr(token->string, '\"'))
		return (1);
	len = ft_strlen(token->string);
	while (token->string[i])
	{
		if ((token->string[i] == '\'' || token->string[i] == '\"')
			&& !between_quotes(token->string, i))
			len--;
		i++;
	}
	if (!removed_quote(token, len))
		return (0);
	return (1);
}
