/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_false_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:52:49 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/09 21:07:21 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	false_var_len(char *str)
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

int	has_false_var(char *string, t_list **env_list, int var_len)
{
	t_list	*env_ptr;
	int		env_sum;
	int		false_var;

	env_ptr = *env_list;
	env_sum = ft_lstsize(*env_list);
	false_var = 0;
	while (env_ptr != NULL)
	{	
		if (!ft_strncmp(string, ((char **) env_ptr->content)[0], var_len))
			return (0);
		env_ptr = env_ptr->next;
	}
	return (1);
}

int	remove_false_var(t_token *token, int var_len, int index)
{
	char	*new_str;
	int		new_len;

	new_len = token->len - var_len - 1;
	if (new_len)
	{
		new_str = (char *) malloc(sizeof(char) * (new_len + 1));
		if (!new_str)
			return (0);
		ft_bzero(new_str, new_len);
		ft_strlcat(new_str, token->string, index + 1);
		ft_strlcat(new_str, &token->string[index + var_len + 1], new_len + 1);
	}
	else
		new_str = ft_strdup("");
	free(token->string);
	token->string = new_str;
	token->len = new_len;
	return (1);
}

int	check_false_var(t_token *token, t_list **env_list)
{
	char	*var;
	char	*ptr;
	int		var_index;
	int		var_len;

	var = ft_strchr(token->string, '$');
	if (!var)
		return (1);
	ptr = token->string;
	var_len = 0;
	while (var)
	{
		var_len = false_var_len(ptr);
		var_index = (int)(var - token->string);
		if (var_quote_status(token->string, var_index, N_QUOTE) != IN_SQUOTE
			&& has_false_var(&token->string[var_index + 1], env_list, var_len)
			&& token->string[var_index + 1] != '?')
		{
			if (!remove_false_var(token, var_len, var_index))
				return (0);
			else
				ptr = token->string;
		}
		else
			ptr = &(token->string[var_index + 1 + var_len]);
		var = ft_strchr(ptr, '$');
	}
	return (1);
}
