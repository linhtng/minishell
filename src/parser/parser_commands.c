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

char	**init_argv_arr(t_list *token_lst)
{
	char	**argv;
	int		size;

	size = count_argv(token_lst);
	argv = (char **) malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	ft_bzero(argv, size);
	argv[size] = NULL;
	return (argv);
}

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
	free(new_cmd);
	return (0);
}

int	save_cmd_lst(t_list **commands, t_list *token_lst, t_token *token)
{
	t_cmd	*new_cmd;
	int		size;
	char	**argv;
	t_list	*token_ptr;

	new_cmd = NULL;
	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd)
	{
		ft_bzero(new_cmd, sizeof(t_cmd));
		token_ptr = token_lst;
		argv = fill_argv(token_lst, token_ptr, token);
		if (argv)
		{
			size = ft_arrlen(argv);
			new_cmd->argv = ft_arrdup(argv, size);
			if (new_cmd->argv)
			{
				new_cmd->pathname = new_cmd->argv[0];
				return (add_cmd_lst(commands, new_cmd));
			}
		}
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
			if (!save_cmd_lst(commands, token_ptr->next, token))
				return (0);
		}
		token_ptr = token_ptr->next;
	}
	return (1);
}