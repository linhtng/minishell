/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_exit_status.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:34:12 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/31 18:35:05 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	get_exit_code_str_heredoc(char **input, char *var, char *exit_status)
{
	char	*new_string;
	int		var_len;
	int		var_index;
	int		new_len;

	var_len = ft_strlen(exit_status);
	new_len = ft_strlen(*input) - 2 + var_len;
	new_string = (char *) malloc(sizeof(char) * (new_len + 1));
	if (!new_string)
		return (0);
	ft_bzero(new_string, new_len);
	var_index = (int)(var - *input);
	ft_strlcat(new_string, *input, var_index + 1);
	ft_strlcat(new_string, exit_status, new_len + 1);
	ft_strlcat(new_string, &(*input)[var_index + var_len + 1], new_len + 1);
	free(*input);
	*input = new_string;
	return (1);
}

int	do_expand_heredoc(char **input, char *var, char *exit_status)
{
	int	var_index;
	int	len;

	while (var)
	{
		var_index = (int)(var - *input);
		if (!get_exit_code_str_heredoc(input, var, exit_status))
			return (0);
		len = ft_strlen(*input);
		var = ft_strnstr(*input, "$?", len);
	}
	return (1);
}

int	expand_exit_status_heredoc(char **input)
{
	char	*var;
	char	*exit_status;
	int		len;

	len = ft_strlen(*input);
	var = ft_strnstr(*input, "$?", len);
	if (!var)
		return (1);
	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
		return (0);
	if (!do_expand_heredoc(input, var, exit_status))
	{
		free(exit_status);
		return (0);
	}
	free(exit_status);
	return (1);
}
