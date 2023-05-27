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

int	save_cmd_lst(t_list **cmds, t_list *tokens, t_token *token, int pipe_input)
{
	t_cmd	*new_cmd;
	t_list	*token_ptr;

	new_cmd = NULL;
	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd)
	{
		ft_bzero(new_cmd, sizeof(t_cmd));
		token_ptr = tokens;
		new_cmd->argv = fill_argv(tokens, token_ptr, token);
		new_cmd->read_fd = pipe_input;
		if (new_cmd->argv)
		{
			new_cmd->pathname = new_cmd->argv[0];
			new_cmd->full_cmd = get_full_cmd(tokens);
			if (new_cmd->full_cmd)
				return (add_cmd_lst(cmds, new_cmd));
			free_arr(new_cmd->argv);
		}
		free(new_cmd);
	}
	return (0);
}

int	seperate_cmds(t_list **cmds, t_list *tokens, t_token *token, int *pipe_in)
{
	t_list	*token_ptr;

	token_ptr = tokens;
	if (parse_pipe(ft_lstlast(*cmds), pipe_in))
	{
		if (!save_cmd_lst(cmds, token_ptr, token, *pipe_in))
			return (0);
	}
	else
		return (0);
	return (1);
}

int	parse_commands(t_list **token_lst, t_list **commands)
{
	t_list	*token_ptr;
	t_token	*token;
	int		pipe_input;

	token_ptr = *token_lst;
	if (!((t_token *) token_ptr->content)->string)
		return (1);
	pipe_input = 0;
	token = ((t_token *) token_ptr->content);
	if (!save_cmd_lst(commands, *token_lst, token, pipe_input))
		return (0);
	while (token_ptr != NULL)
	{
		token = ((t_token *) token_ptr->content);
		if (token->type == PIPE)
		{
			if (!seperate_cmds(commands, token_ptr->next, token, &pipe_input))
				return (0);
		}
		token_ptr = token_ptr->next;
	}
	return (1);
}
