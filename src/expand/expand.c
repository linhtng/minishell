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

int	get_expanded_str(t_token *token, char *var, char **env_list, int env_len)
{
	char	*new_str;
	int		new_len;
	int		var_index;
	int		var_name;

	var_name = ft_strlen(env_list[0]);
	new_len = token->len - 1 - var_name + env_len;
	if (new_len)
	{
		new_str = (char *) malloc(sizeof(char) * (new_len + 1));
		if (!new_str)
			return (0);
		ft_bzero(new_str, new_len);
		var_index = (int)(var - token->string);
		ft_strlcat(new_str, token->string, var_index);
		if (env_list[1])
			ft_strlcat(new_str, env_list[1], new_len + 1);
		ft_strlcat(new_str, &token->string[var_index + var_name], new_len + 1);
	}
	else
		new_str = ft_strdup("");
	free(token->string);
	token->string = new_str;
	token->len = new_len;
	return (1);
}

int	replace_var_value(t_token *token, char **env_list, int env_len)
{
	char	*var;
	char	*ptr;
	int		var_index;

	var = ft_strnstr(token->string, env_list[0], token->len);
	if (!var)
		return (1);
	ptr = token->string;
	while (var)
	{
		var_index = (int)(var - token->string);
		if (var_index && token->string[var_index - 1] == '$'
			&& var_quote_status(token->string, var_index, N_QUOTE) != IN_SQUOTE)
		{
			if (!get_expanded_str(token, var, env_list, env_len))
				return (0);
			ptr = token->string;
		}
		else
			ptr = &(token->string[var_index + ft_strlen(env_list[0])]);
		var = ft_strnstr(ptr, env_list[0], token->len);
	}
	return (1);
}

int	expand_var(t_token *token, t_list **env_list)
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
			if (!replace_var_value(token, env_ptr->content, env_len))
				return (0);
		}
		env_ptr = env_ptr->next;
	}
	if (expand_exit_status(token))
		return (1);
	return (0);
}

int	expand_empty_var(t_token *token, t_list **env_list)
{
	t_list	*env_ptr;
	int		env_len;

	env_ptr = *env_list;
	env_len = 0;
	while (env_ptr != NULL)
	{	
		if (((char **) env_ptr->content)[1] == NULL)
		{
			if (!replace_var_value(token, env_ptr->content, env_len))
				return (0);
		}
		env_ptr = env_ptr->next;
	}
	return (1);
}

int	expand(t_list **tokens, t_list **env_list)
{
	t_list	*token_ptr;

	token_ptr = *tokens;
	while (token_ptr != NULL)
	{
		if (((t_token *) token_ptr->content)->type == VAR)
		{
			if (!check_false_var(token_ptr->content, env_list)
				|| !expand_empty_var(token_ptr->content, env_list)
				|| !expand_var(token_ptr->content, env_list))
				return (0);
		}
		if (!apply_quoting_rules(token_ptr->content))
			return (0);
		token_ptr = token_ptr->next;
	}
	return (1);
}
