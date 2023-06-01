/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:43:09 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/27 19:54:59 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_list **token_ptr,
							t_token **token,
							t_cmd **cmd,
							int append)
{
	int	fd;

	*token_ptr = (*token_ptr)->next;
	*token = ((t_token *)(*token_ptr)->content);
	if (append)
		fd = open((*token)->string, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open((*token)->string, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd >= 0)
	{
		if ((*cmd)->write_fd != 0 && (*cmd)->write_fd != STDOUT_FILENO)
			close((*cmd)->write_fd);
		(*cmd)->write_fd = fd;
		return (1);
	}
	else
	{
		print_error(2, "unable to open file for writing: ", (*token)->string);
		return (0);
	}
}

static int	redirect_input(t_list **token_ptr, t_token **token, t_cmd **cmd)
{
	int	fd;

	*token_ptr = (*token_ptr)->next;
	*token = ((t_token *)(*token_ptr)->content);
	fd = open((*token)->string, O_RDONLY);
	if (fd >= 0)
	{
		if ((*cmd)->read_fd != 0 && (*cmd)->read_fd != STDIN_FILENO)
			close((*cmd)->read_fd);
		(*cmd)->read_fd = fd;
		return (1);
	}
	else
	{
		print_error(2, "unable to open file for reading: ", (*token)->string);
		return (0);
	}
}

int	get_redirects(t_list *token_lst, t_cmd **cmd, t_list **env_list)
{
	int		ret;
	t_token	*token;

	ret = 1;
	token = ((t_token *) token_lst->content);
	while (token_lst != NULL && token->type != PIPE)
	{
		if (token->type == OUTPUT_TRUNC)
			ret = redirect_output(&token_lst, &token, cmd, 0);
		else if (token->type == OUTPUT_APP)
			ret = redirect_output(&token_lst, &token, cmd, 1);
		else if (token->type == INPUT)
			ret = redirect_input(&token_lst, &token, cmd);
		else if (token->type == HERE_DOC)
			ret = do_heredoc(&token_lst, &token, cmd, env_list);
		if (!ret)
		{
			close_redirects(&(*cmd)->write_fd, &(*cmd)->read_fd);
			break ;
		}
		token_lst = token_lst->next;
		if (token_lst)
			token = ((t_token *) token_lst->content);
	}
	return (ret);
}
