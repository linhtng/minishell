/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:23:30 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/24 21:07:58 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_str_heredoc(char **input, char *var, char **env_list, int env_len)
{
	char	*new_str;
	int		new_len;
	int		var_index;
	int		var_name_len;

	var_name_len = ft_strlen(env_list[0]);
	new_len = ft_strlen(*input) - 1 - var_name_len + env_len;
	if (new_len)
	{
		new_str = (char *) malloc(sizeof(char) * (new_len + 1));
		if (!new_str)
			return (0);
		ft_bzero(new_str, new_len);
		var_index = (int)(var - *input);
		ft_strlcat(new_str, *input, var_index);
		if (env_list[1])
			ft_strlcat(new_str, env_list[1], new_len + 1);
		ft_strlcat(new_str, &(*input)[var_index + var_name_len], new_len + 1);
	}
	else
		new_str = ft_strdup("");
	free(*input);
	*input = new_str;
	return (1);
}

int	replace_var_value_heredoc(char **input, char **env_list, int env_len)
{
	char	*var;
	int		var_index;
	char	*ptr;

	var = ft_strnstr(*input, env_list[0], ft_strlen(*input));
	if (!var)
		return (1);
	ptr = *input;
	while (var)
	{
		var_index = (int)(var - *input);
		if (var_index && (*input)[var_index - 1] == '$')
		{
			if (!expand_str_heredoc(input, var, env_list, env_len))
				return (0);
			ptr = *input;
		}
		else
			ptr = &(*input)[var_index + ft_strlen(env_list[0])];
		var = ft_strnstr(ptr, env_list[0], ft_strlen(*input));
	}
	return (1);
}

int	expand_empty_var_heredoc(char **input, t_list **env_list)
{
	t_list	*env_ptr;
	int		env_len;

	env_ptr = *env_list;
	env_len = 0;
	while (env_ptr != NULL)
	{	
		if (((char **) env_ptr->content)[1] == NULL)
		{
			if (!replace_var_value_heredoc(input, env_ptr->content, env_len))
				return (0);
		}
		env_ptr = env_ptr->next;
	}
	return (1);
}

int	expand_var_heredoc(char **input, t_list **env_list)
{
	t_list	*env_ptr;
	int		env_len;

	env_ptr = *env_list;
	env_len = 0;
	while (env_ptr != NULL)
	{	
		if (((char **) env_ptr->content)[1] != NULL)
		{
			env_len = ft_strlen(((char **) env_ptr->content)[1]);
			if (!replace_var_value_heredoc(input, env_ptr->content, env_len))
				return (0);
		}
		env_ptr = env_ptr->next;
	}
	return (1);
}

int	expand_heredoc(char **input, t_list **env_list)
{
	t_list	*env_ptr;
	int		len;

	if (!ft_strchr(*input, '$'))
		return (1);
	env_ptr = *env_list;
	len = 0;
	if (check_false_var_heredoc(input, env_list)
		&& expand_empty_var_heredoc(input, env_list)
		&& expand_var_heredoc(input, env_list)
		&& expand_exit_status_heredoc(input))
		return (1);
	return (0);
}
