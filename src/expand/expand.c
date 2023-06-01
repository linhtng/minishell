/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:23:30 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/24 21:07:58 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_enpanded_str(t_token *token, char *var, char **env_list)
{
	char	*new_string;
	int		new_len;
	int		var_index;
	int		var_name_len;

	new_len = token->len - ft_strlen(env_list[0]) + ft_strlen(env_list[1]);
	new_string = (char *) malloc(sizeof(char) * new_len);
	if (!new_string)
		return (0);
	ft_bzero(new_string, new_len);
	var_index = (int)(var - token->string);
	var_name_len = ft_strlen(env_list[0]);
	ft_strlcat(new_string, token->string, var_index);
	ft_strlcat(new_string, env_list[1], new_len);
	ft_strlcat(new_string, &token->string[var_index + var_name_len], new_len);
	free(token->string);
	token->string = new_string;
	token->len = new_len;
	return (1);
}

int	get_envvar_len(char *str, char *var_name)
{
	int		i;
	int		len;
	char	*var;

	var = ft_strnstr(str, var_name, ft_strlen(str));
	if (!ft_strchr(str, '$') || !var)
		return (0);
	i = (int)(var - str);
	if (str[i - 1] != '$')
		return (0);
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

int	replace_var_value(t_token *token, char **env_list)
{
	char	*var;
	char	*ptr;
	int		var_index;

	var = ft_strnstr(token->string, env_list[0], token->len);
	if (!var || !env_list[1])
		return (1);
	ptr = token->string;
	while (var)
	{
		var_index = (int)(var - token->string);
		if (var_quote_status(token->string, var_index, N_QUOTE) != IN_SQUOTE
			&& get_envvar_len(ptr, env_list[0]) == (int) ft_strlen(env_list[0]))
		{
			if (!get_enpanded_str(token, var, env_list))
				return (0);
			else
				ptr = &(token->string[var_index - 1 + ft_strlen(env_list[1])]);
		}
		else
			ptr = &(token->string[var_index - 1 + ft_strlen(env_list[0])]);
		var = ft_strnstr(ptr, env_list[0], token->len);
	}
	return (1);
}

int	expand_var(t_token *token, t_list **env_list)
{
	t_list	*env_ptr;

	env_ptr = *env_list;
	if (check_false_var(token, env_list))
	{
		while (env_ptr != NULL)
		{	
			if (!replace_var_value(token, env_ptr->content))
				return (0);
			env_ptr = env_ptr->next;
		}
		if (expand_exit_status(token))
			return (1);
	}
	return (0);
}

int	expand(t_list **tokens, t_list **env_list)
{
	t_list	*token_ptr;

	token_ptr = *tokens;
	while (token_ptr != NULL)
	{
		if (((t_token *) token_ptr->content)->type == VAR)
		{
			if (!expand_var(token_ptr->content, env_list))
				return (0);
		}
		if (!apply_quoting_rules(token_ptr->content))
			return (0);
		token_ptr = token_ptr->next;
	}
	return (1);
}
