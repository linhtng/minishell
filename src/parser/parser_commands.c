/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:09:42 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/22 18:34:38 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**fill_argv(t_list *token_lst, t_list *tok_ptr, t_token *token)
{
	int		i;
	char	**argv;

	i = 0;
	argv = init_argv_arr(token_lst);
	if (argv)
	{
		while (tok_ptr != NULL && ((t_token *) tok_ptr->content)->type != PIPE)
		{
			token = ((t_token *) tok_ptr->content);
			if (token->type >= HERE_DOC)
			{
				if (tok_ptr->next->next != NULL)
					tok_ptr = tok_ptr->next->next;
				else
					break ;
			}
			else if (token->type == WORD || token->type == VAR)
			{
				if (!add_argv_cmd(token, argv, &i, &tok_ptr))
					return (NULL);
			}
		}
	}
	return (argv);
}

int	add_cmd_lst(t_list **commands, t_cmd *new_cmd)
{
	t_list	*new_elem;

	new_elem = NULL;
	new_elem = ft_lstnew(new_cmd);
	if (new_elem)
	{
		ft_lstadd_back(commands, new_elem);
		return (1);
	}
	free_arr(new_cmd->argv);
	free(new_cmd->full_cmd);
	free(new_cmd);
	return (0);
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

int	save_cmd_lst(t_list **commands, t_list *token_lst, t_token *token)
{
	t_cmd	*new_cmd;
	t_list	*token_ptr;

	new_cmd = NULL;
	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd)
	{
		ft_bzero(new_cmd, sizeof(t_cmd));
		token_ptr = token_lst;
		new_cmd->argv = fill_argv(token_lst, token_ptr, token);
		if (new_cmd->argv)
		{
			new_cmd->pathname = new_cmd->argv[0];
			new_cmd->full_cmd = get_full_cmd(token_lst);
			if (new_cmd->full_cmd)
				return (add_cmd_lst(commands, new_cmd));
			free_arr(new_cmd->argv);
		}
		free(new_cmd);
	}
	return (0);
}

int	parse_commands(t_list **token_lst, t_list **commands)
{
	t_list	*token_ptr;
	t_token	*token;

	token_ptr = *token_lst;
	if (!((t_token *) token_ptr->content)->string)
		return (1);
	token = ((t_token *) token_ptr->content);
	if (!save_cmd_lst(commands, *token_lst, token))
		return (0);
	while (token_ptr != NULL)
	{
		token = ((t_token *) token_ptr->content);
		if (token->type == PIPE)
		{
			if (parse_pipe(ft_lstlast(*commands)))
			{
				if (!save_cmd_lst(commands, token_ptr->next, token))
					return (0);
			}
			else
				return (0);
		}
		token_ptr = token_ptr->next;
	}
	return (1);
}
