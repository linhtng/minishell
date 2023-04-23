/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:57:47 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/23 19:39:23 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	count_occurences(const char *str, char c)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	get_quote_status(char *input, int i, int status)
{
	if (status == N_QUOTE && input[i] == '\'')
		return (IN_SQUOTE);
	if (status == N_QUOTE && input[i] == '\"')
		return (IN_DQUOTE);
	if (status == IN_SQUOTE && input[i] == '\'')
		return (N_QUOTE);
	if (status == IN_DQUOTE && input[i] == '\"')
		return (N_QUOTE);
	return (status);
}

int	token_type(char *input, int i)
{
	if (ft_isspace(input[i]))
		return (SPACE);
	if (input[i] == '|')
		return (PIPE);
	if (input[i] == '<' && input[i + 1] == '<')
		return (HERE_DOC);
	if (input[i] == '>' && input[i + 1] == '>')
		return (OUTPUT_APP);
	if (input[i] == '<')
		return (INPUT);
	if (input[i] == '>')
		return (OUTPUT_TRUNC);
	if (input[i] == '\0')
		return (NULL_CHAR);
	return (0);
}

void	del_token(void *content)
{
	free(((t_token *) content)->string);
	free(content);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}