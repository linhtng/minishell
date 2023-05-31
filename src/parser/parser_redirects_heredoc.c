/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirects_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:35:56 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/31 18:03:53 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	heredoc_prompt_signal(char **input_buf)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	setup_signals_heredoc();
	close_echoctl(&t);
	ft_putstr_fd("heredoc> ", 1);
	*input_buf = get_next_line(STDIN_FILENO);
	reset_echoctl(&t);
}

int	heredoc_loop(t_token *token, int heredoc_pipe, t_list **env, char **input)
{
	char	*heredoc_delim;
	char	*ori_delim;

	heredoc_delim = token->string;
	ori_delim = token->ori_string;
	while (*input && (ft_strlen(*input) != (size_t)(token->len + 1)
		|| ft_strncmp(*input, heredoc_delim, token->len)) != 0)
	{
		if (!ft_strchr(ori_delim, '\'') && !ft_strchr(ori_delim, '\"'))
		{
			if (!expand_heredoc_var(input, env))
				return (0);
		}
		if (write(heredoc_pipe, *input, ft_strlen(*input)) == -1)
		{
			print_error(1, "error writing heredoc buffer");
			close(heredoc_pipe);
			return (0);
		}
		if (*input)
			free(*input);
		heredoc_prompt_signal(input);
	}
	return (1);
}

static int	heredoc_prompt(t_token *token, int heredoc_pipe, t_list **env_list)
{
	char	*input_buf;
	int		ret;

	ret = 0;
	heredoc_prompt_signal(&input_buf);
	ret = heredoc_loop(token, heredoc_pipe, env_list, &input_buf);
	if (!input_buf && !g_exit_status)
		return (ret);
	else if (!input_buf && g_exit_status)
		return (0);
	if (input_buf)
		free(input_buf);
	return (ret);
}

int	do_heredoc(t_list **token_ptr, t_token **token, t_cmd **cmd, t_list **env)
{
	int	pipefd[2];

	*token_ptr = (*token_ptr)->next;
	*token = ((t_token *)(*token_ptr)->content);
	if (pipe(pipefd) == -1)
	{
		print_error(1, "unable to create pipe for heredoc");
		return (0);
	}
	if (!heredoc_prompt(*token, pipefd[1], env))
		return (0);
	close(pipefd[1]);
	if ((*cmd)->read_fd != 0 && (*cmd)->read_fd != STDIN_FILENO)
		close((*cmd)->read_fd);
	(*cmd)->read_fd = pipefd[0];
	return (1);
}
