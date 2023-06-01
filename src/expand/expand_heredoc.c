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

int	get_expanded_str_heredoc(char **input, char *var, char **env_list, int *len)
{
	char	*new_string;
	int		new_len;
	int		var_index;
	int		var_name_len;

	new_len = *len - ft_strlen(env_list[0]) + ft_strlen(env_list[1]);
	new_string = (char *) malloc(sizeof(char) * new_len);
	if (!new_string)
		return (0);
	ft_bzero(new_string, new_len);
	var_index = (int)(var - *input);
	var_name_len = ft_strlen(env_list[0]);
	ft_strlcat(new_string, *input, var_index);
	ft_strlcat(new_string, env_list[1], new_len);
	ft_strlcat(new_string, &(*input)[var_index + var_name_len], new_len);
	free(*input);
	*input = new_string;
	*len = new_len;
	return (1);
}

int	replace_var_value_heredoc(char **input, char **env_list, int len)
{
	char	*var;
	int		var_index;

	var = ft_strnstr(*input, env_list[0], len);
	if (!var || !env_list[1])
		return (1);
	while (var)
	{
		var_index = (int)(var - *input);
		if (get_envvar_len(*input, env_list[0]) == (int) ft_strlen(env_list[0]))
		{	
			if (!get_expanded_str_heredoc(input, var, env_list, &len))
				return (0);
		}
		var = ft_strnstr(*input, env_list[0], len);
	}
	return (1);
}

int	expand_heredoc_var(char **input, t_list **env_list)
{
	t_list	*env_ptr;
	int		len;
	char	*var;

	var = ft_strchr(*input, '$');
	if (!var)
		return (1);
	env_ptr = *env_list;
	len = 0;
	if (check_false_var_heredoc(input, env_list))
	{
		while (env_ptr != NULL)
		{	
			len = ft_strlen(*input);
			if (!replace_var_value_heredoc(input, env_ptr->content, len))
				return (0);
			env_ptr = env_ptr->next;
		}
		if (expand_exit_status_heredoc(input))
			return (1);
	}
	return (0);
}
