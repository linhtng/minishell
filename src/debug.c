/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:53:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/24 18:29:08 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_tokens_list(t_list *list)
{
    t_list	*ptr;
	int		i;
	int		type_num;

	ptr = list;
	i = 1;
	while (ptr)
    {
		printf("token number %d has content: %s and type: ", i, ((t_token *) ptr->content)->string);
		type_num = ((t_token *) ptr->content)->type;
		if (type_num == WORD)
			printf("WORD\n");
		else if (type_num == SPACE_CHAR)
			printf("SPACE\n");
		else if (type_num == PIPE)
			printf("PIPE\n");
		else if (type_num == HERE_DOC)
			printf("HERE_DOC\n");
		else if (type_num == OUTPUT_APP)
			printf("OUTPUT_APP\n");
		else if (type_num == INPUT)
			printf("INPUT\n");
		else if (type_num == OUTPUT_TRUNC)
			printf("OUTPUT_TRUNC\n");
		else if (type_num == NULL_CHAR)
			printf("NULL_CHAR\n");
		else if (type_num == VAR)
			printf("VAR\n");
		ptr = ptr->next;
		i++;
    }
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void    print_cmd_list(t_list *list)
{
    t_list	*ptr;
	t_cmd	*cmd;
	int		i;

	ptr = list;
	i = 1;
	//printf("Command list:\n");
	while (ptr)
    {
		cmd = ((t_cmd *) ptr->content);
		printf("cmd number %d has argv list:\n", i);
		print_arr(cmd->argv);
		printf("pathname: %s\n", cmd->pathname);
		printf("read_fd: %d\n", cmd->read_fd);
		printf("write_fd: %d\n", cmd->write_fd);
		ptr = ptr->next;
		i++;
    }
}

/* 
int	add_token_lst(t_token *token, char *input, int type, t_list **tokens)
{
	char	*str_content;
	t_token	*new_token;
	t_list	*new_lem;

	new_lem = NULL;
    str_content = ft_substr(input, token->start_index, token->len);
	if (str_content)
	{
		new_token = (t_token *) malloc(sizeof(t_token));
		if (new_token)
		{
			new_token->string = str_content;
			new_token->type = type;
			new_token->start_index = token->start_index;
			new_token->len = token->len;
			new_lem = ft_lstnew(new_token);
			if (new_lem)
			{
				ft_lstadd_back(tokens, new_lem);
				return (1);
			}
		}
	}
	return (0);
}

int	save_token_symbol(t_token *token, char *input, t_list **token_lst, int *i)
{
	if (token_type(input, *i - 1) == 0)
		token->start_index = *i;
	token->len = 1;
	if (token->type == HERE_DOC || token->type == OUTPUT_APP)
	{
		token->len = 2;
		(*i)++;
	}
	if (!add_token_lst(token, input, token->type, token_lst))
		return (0);
	return (1);
}

int	save_token(char *input, int *i, t_token *token, t_list **token_lst)
{
	int		type;

	type = token_type(input, *i);
	if (type != 0)
	{
		if (*i && token_type(input, *i - 1) == 0)
		{
			token->len = *i - token->start_index;
			if (!add_token_lst(token, input, WORD, token_lst))
				return (-1);
		}
		if (type != SPACE && type != NULL_CHAR)
		{
			token->type = type;
			if (!save_token_symbol(token, input, token_lst, i))
				return (-1);
		}
		token->start_index = *i + 1;
	}
	return (token->start_index);
}

void	token_lst(char *input, int size, t_list **tokens_lst)
{
	t_token	*token;
	int		i;
	int		status;

	token = (t_token *) malloc(sizeof(t_token));
	if (token)
	{
		ft_bzero(token, sizeof(t_token));
		i = 0;
		status = N_QUOTE;
		while (i <= size)
		{
			status = get_quote_status(input, i, status);
			if (status == N_QUOTE)
				token->start_index = save_token(input, &i, token, tokens_lst);
			if (token->start_index == -1)
			{
				ft_lstclear(tokens_lst, del_token);
				free(token);
				return (perror("Malloc error when creating token list"));
			}
			i++;
		}
		free(token);
	}
}

//int	main(int arc, char **arv)
int main(void)
{
	int size;
    t_list	*tokens_lst;
    char *input;

	tokens_lst = NULL;
	 	if (arc == 2)
    {
        size = ft_strlen(arv[1]);
        tokens_lst = token_lst(arv[1], size);
        print_list(tokens_lst);
    }
    input = readline("minishell$  ");
    //input = "echo w>";
    size = ft_strlen(input);
    token_lst(input, size, &tokens_lst);
    print_tokens_list(tokens_lst);
	return (0);
} */