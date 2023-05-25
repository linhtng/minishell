/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:57:47 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/29 18:40:51 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (SPACE_CHAR);
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
