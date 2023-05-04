/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 20:23:30 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/02 20:26:17 by thuynguy         ###   ########.fr       */
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
	new_string = (char *) malloc(sizeof(char) * (new_len + 1));
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

int	replace_var_value(t_token *token, char **env_list)
{
	char	*var;
	char	*ptr;
	int		var_index;

	var = NULL;
	var = ft_strnstr(token->string, env_list[0], token->len);
	if (!var)
		return (1);
	ptr = token->string;
	var_index = (int)(var - token->string);
	while (var)
	{
		if (var_quote_status(token->string, var_index, N_QUOTE) != IN_SQUOTE)
		{
			if (!get_enpanded_str(token, var, env_list))
				return (0);
			else
				ptr = &(token->string[token->len - 1]);
		}
		else
			ptr = &(token->string[var_index + ft_strlen(env_list[0])]);
		var = ft_strnstr(ptr, env_list[0], token->len);
		var_index = (int)(var - token->string);
	}
	return (1);
}

int	expand(t_list **tokens, t_list **env_list)
{
	t_list	*token_ptr;
	t_list	*env_ptr;

	token_ptr = *tokens;
	env_ptr = *env_list;
	while (token_ptr != NULL)
	{
		if (((t_token *) token_ptr->content)->type == VAR)
		{
			while (env_ptr != NULL)
			{	
				if (!replace_var_value(token_ptr->content, env_ptr->content))
					return (0);
				env_ptr = env_ptr->next;
			}
		}
		token_ptr = token_ptr->next;
		env_ptr = *env_list;
	}
	return (1);
}
