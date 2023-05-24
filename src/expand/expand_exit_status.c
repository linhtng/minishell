/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:02:48 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/24 21:01:06 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	var_quote_status(char *string, int index, int q_status)
{
	int	i;

	i = 0;
	while (i < index)
	{
		q_status = get_quote_status(string, i, q_status);
		i++;
	}
	return (q_status);
}

int	get_exit_code_str(t_token *token, char *var, char *exit_status, char **ptr)
{
	char	*new_string;
	int		var_len;
	int		var_index;

	var_len = ft_strlen(exit_status);
	token->len = token->len - 2 + var_len;
	new_string = (char *) malloc(sizeof(char) * (token->len + 1));
	if (!new_string)
		return (0);
	ft_bzero(new_string, token->len);
	var_index = (int)(var - token->string);
	ft_strlcat(new_string, token->string, var_index + 1);
	ft_strlcat(new_string, exit_status, token->len + 1);
	ft_strlcat(new_string, &token->string[var_index + var_len + 1],
		token->len + 1);
	free(token->string);
	token->string = new_string;
	*ptr = &token->string[var_index + var_len];
	return (1);
}

int	do_expand(t_token *token, char *var, char *exit_status, char *ptr)
{
	int	var_index;

	while (var)
	{
		var_index = (int)(var - token->string);
		if (var_quote_status(token->string, var_index, N_QUOTE) != IN_SQUOTE)
		{
			if (!get_exit_code_str(token, var, exit_status, &ptr))
				return (0);
		}
		else
			ptr = &(token->string[var_index + 2]);
		var = ft_strnstr(ptr, "$?", token->len);
	}
	return (1);
}

int	expand_exit_status(t_token *token)
{
	char	*var;
	char	*ptr;
	char	*exit_status;

	var = ft_strnstr(token->string, "$?", token->len);
	if (!var)
		return (1);
	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (0);
	ptr = token->string;
	if (!do_expand(token, var, exit_status, ptr))
	{
		free(exit_status);
		return (0);
	}
	free(exit_status);
	return (1);
}
