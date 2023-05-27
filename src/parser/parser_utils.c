/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:01:00 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/23 21:03:59 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*mns_strjoin(char *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		ret;
	char	*res;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = len1 + len2;
	res = (char *) malloc(sizeof(*s1) * (ret + 1));
	if (!res)
		return (NULL);
	ft_memmove(res, s1, len1);
	ft_memmove(&res[len1], s2, len2);
	res[ret] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*get_full_cmd(t_list *token_lst)
{
	t_list	*token_ptr;
	t_token	*token;
	char	*full_cmd;

	token_ptr = token_lst;
	token = ((t_token *) token_ptr->content);
	full_cmd = NULL;
	full_cmd = ft_strdup(token->string);
	if (!full_cmd)
		return (NULL);
	while (token_ptr->next != NULL && token->type != PIPE)
	{
		token_ptr = token_ptr->next;
		token = ((t_token *) token_ptr->content);
		if (token->type != PIPE)
		{
			full_cmd = mns_strjoin(mns_strjoin(full_cmd, " "), token->string);
			if (!full_cmd)
				return (NULL);
		}
	}
	return (full_cmd);
}
