/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:28:29 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/30 17:15:52 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmds(void *content)
{
	free_arr(((t_cmd *) content)->argv);
	if (((t_cmd *) content)->read_fd != STDIN_FILENO)
	{
		close(((t_cmd *) content)->read_fd);
		((t_cmd *) content)->read_fd = STDIN_FILENO;
	}
	if (((t_cmd *) content)->write_fd != STDOUT_FILENO
		&& ((t_cmd *) content)->write_fd != STDIN_FILENO)
	{
		close(((t_cmd *) content)->write_fd);
		((t_cmd *) content)->write_fd = STDOUT_FILENO;
	}
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

int	parse_pipe(t_list *commands, int *pipe_input)
{
	t_cmd	*cmd;
	int		pipe_fds[2];

	cmd = ((t_cmd *) commands->content);
	if (pipe(pipe_fds) != 0)
	{
		perror("Creating pipe failed.");
		return (0);
	}
	*pipe_input = pipe_fds[0];
	if (cmd->write_fd != 0 && cmd->write_fd != STDOUT_FILENO)
		close(cmd->write_fd);
	cmd->write_fd = pipe_fds[1];
	return (1);
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
