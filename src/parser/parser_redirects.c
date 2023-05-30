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
		print_error(2, "unable to open file for writing: ", (*token)->string);
		return (0);
	}
}

static int	heredoc_prompt(char *heredoc_delim, int heredoc_pipe)
{
	char	*input_buf;

	ft_putstr_fd("heredoc> ", 1);
	input_buf = get_next_line(STDIN_FILENO);
	while (input_buf && (ft_strlen(input_buf) != (ft_strlen(heredoc_delim) + 1)
			|| ft_strncmp(input_buf, heredoc_delim,
				ft_strlen(heredoc_delim))) != 0)
	{
		if (write(heredoc_pipe, input_buf, ft_strlen(input_buf)) == -1)
		{
			print_error(1, "error writing heredoc buffer");
			close(heredoc_pipe);
			return (0);
		}
		free(input_buf);
		ft_putstr_fd("heredoc> ", 1);
		input_buf = get_next_line(STDIN_FILENO);
	}
	if (input_buf)
		free(input_buf);
	return (1);
}

static int	do_the_heredoc(t_list **token_ptr, t_token **token, t_cmd **cmd)
{
	int	pipefd[2];

	*token_ptr = (*token_ptr)->next;
	*token = ((t_token *)(*token_ptr)->content);
	if (pipe(pipefd) == -1)
	{
		print_error(1, "unable to create pipe for heredoc");
		return (0);
	}
	if (!heredoc_prompt((*token)->string, pipefd[1]))
		return (0);
	close(pipefd[1]);
	if ((*cmd)->read_fd != 0 && (*cmd)->read_fd != STDIN_FILENO)
		close((*cmd)->read_fd);
	(*cmd)->read_fd = pipefd[0];
	return (1);
}

int	get_redirects(t_list *token_lst, t_cmd **cmd)
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
			ret = do_the_heredoc(&token_lst, &token, cmd);
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
