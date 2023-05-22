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

char	**fill_argv(t_list *token_lst)
{
	t_list	*token_ptr;
	t_token	*token;
	int		i;
	char	**argv;

	token_ptr = token_lst;
	i = 0;
	argv = init_argv_arr(token_lst);
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
			add_argv_cmd(token, argv, &i);
		token_ptr = token_ptr->next;
	}
	return (argv);
}

int	save_cmd_lst(t_list **commands, t_list *token_lst)
{
	t_list	*new_elem;
	t_cmd	*new_cmd;
	int		size;
	char	**argv;

	new_elem = NULL;
	new_cmd = NULL;
	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd)
	{
		ft_bzero(new_cmd, sizeof(t_cmd));
		argv = fill_argv(token_lst);
		size = ft_arrlen(argv);
		new_cmd->argv = ft_arrdup(argv, size);
		if (!new_cmd->argv)
			return (0);
		new_cmd->pathname = new_cmd->argv[0];
		new_elem = ft_lstnew(new_cmd);
		if (new_elem)
		{
			ft_lstadd_back(commands, new_elem);
			return (1);
		}
	}
	return (0);
}

int	parse_commands(t_list **token_lst, t_list **commands)
{
	t_list	*token_ptr;
	t_token	*token;
	int		i;

	token_ptr = *token_lst;
	if (!((t_token *) token_ptr->content)->string)
		return (1);
	i = 0;
	save_cmd_lst(commands, *token_lst);
	while (token_ptr != NULL)
	{
		token = ((t_token *) token_ptr->content);
		if (token->type == PIPE)
			save_cmd_lst(commands, token_ptr->next);
		token_ptr = token_ptr->next;
	}
	return (1);
}
