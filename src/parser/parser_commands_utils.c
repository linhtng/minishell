/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:28:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/22 18:33:52 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmds(void *content)
{
	free_arr(((t_cmd *) content)->argv);
	free(content);
}

int	count_argv(t_list *token_lst)
{
	t_list	*token_ptr;
	t_token	*token;
	int		count;

	token_ptr = token_lst;
	if (!token_ptr)
		return (0);
	count = 0;
	token = ((t_token *) token_ptr->content);
	while (token_ptr != NULL && token->type != PIPE)
	{
		token = ((t_token *) token_ptr->content);
		if (token->type >= HERE_DOC)
		{
			if (token_ptr->next->next != NULL)
				token_ptr = token_ptr->next;
			else
				break ;
		}
		else if (token->type == WORD || token->type == VAR)
			count++;
		token_ptr = token_ptr->next;
	}
	return (count);
}

int	add_argv_cmd(t_token *token, char **argv, int *i, t_list **token_ptr)
{
	argv[*i] = ft_strdup(token->string);
	if (!argv[*i])
	{
		free_arr(argv);
		return (0);
	}
	(*i)++;
	*token_ptr = (*token_ptr)->next;
	return (1);
}
