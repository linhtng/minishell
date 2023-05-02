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

char	*enpanded_str(t_token *token, char *var, char **env_list, int new_len)
{
	char	*old_string;
	char	*new_string;
	int		var_index;
	int		var_name_len;

	new_string = (char *) malloc(sizeof(char) * (new_len + 1));
	if (new_string)
	{
		old_string = token->string;
		var_index = (int)(var - old_string);
		var_name_len = ft_strlen(env_list[0]);
		ft_memmove(new_string, old_string, var_index - 1);
		ft_strlcat(new_string, env_list[1], new_len);
		ft_strlcat(new_string, &old_string[var_index + var_name_len], new_len);
		free(old_string);
	}
	return (new_string);
}

int	replace_var_value(t_token *token, char **env_list)
{
	char	*var;
	char	*new_string;
	int		new_len;

	var = NULL;
	new_len = 0;
	new_string = NULL;
	var = ft_strnstr(token->string, env_list[0], token->len);
	if (var)
	{
		new_len = token->len - ft_strlen(env_list[0]) + ft_strlen(env_list[1]);
		new_string = enpanded_str(token, var, env_list, new_len);
		if (!new_string)
			return (0);
		token->string = new_string;
		token->len = new_len;
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
	}
	return (1);
}
