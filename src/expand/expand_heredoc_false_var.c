/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_false_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:52:49 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/15 17:12:04 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	false_var_len_heredoc(char *str)
{
	int		i;
	int		len;
	char	*var;

	var = ft_strchr(str, '$');
	if (!var)
		return (0);
	i = (int)(var - str);
	i++;
	len = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			break ;
		i++;
		len++;
	}
	return (len);
}

int	has_false_var_heredoc(char *string, t_list **env_list, int var_len)
{
	t_list	*env_ptr;
	char	*env_name;

	env_ptr = *env_list;
	while (env_ptr != NULL)
	{	
		env_name = ((char **) env_ptr->content)[0];
		if (!ft_strncmp(string, env_name, var_len)
			&& var_len == (int) ft_strlen(env_name))
			return (0);
		env_ptr = env_ptr->next;
	}
	return (1);
}

int	remove_false_var_heredoc(char **input, int var_len, char *var)
{
	char	*new_str;
	int		new_len;
	int		index;
	int		ori_len;

	index = (int)(var - *input);
	ori_len = ft_strlen(*input);
	new_len = ori_len - var_len - 1;
	if (new_len)
	{
		new_str = (char *) malloc(sizeof(char) * (new_len + 1));
		if (!new_str)
			return (0);
		ft_bzero(new_str, new_len);
		ft_strlcat(new_str, *input, index + 1);
		ft_strlcat(new_str, &(*input)[index + var_len + 1], new_len + 1);
	}
	else
		new_str = ft_strdup("");
	free(*input);
	*input = new_str;
	return (1);
}

int	remove_var_cond_heredoc(char *string, char *var, t_list **env, int var_len)
{
	int	var_index;

	var_index = (int)(var - string);
	if (has_false_var_heredoc(&string[var_index + 1], env, var_len)
		&& string[var_index + 1] != '?')
		return (1);
	return (0);
}

int	check_false_var_heredoc(char **input, t_list **env_list)
{
	char	*var;
	char	*ptr;
	int		var_len;

	var = ft_strchr(*input, '$');
	if (!var)
		return (1);
	ptr = *input;
	var_len = 0;
	while (var)
	{
		var_len = false_var_len_heredoc(ptr);
		if (var_len
			&& remove_var_cond_heredoc(*input, var, env_list, var_len))
		{
			if (!remove_false_var_heredoc(input, var_len, var))
				return (0);
			else
				ptr = *input;
		}
		else
			ptr = &((*input)[(int)(var - *input) + 1 + var_len]);
		var = ft_strchr(ptr, '$');
	}
	return (1);
}
