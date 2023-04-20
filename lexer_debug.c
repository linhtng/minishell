/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:53:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/20 18:53:45 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./includes/minishell.h"

void    print_list(t_list *list)
{
    t_list	*ptr;

	ptr = list;
	while (ptr)
    {
        //printf("content: %s, quote:	%d, type: %d\n", ptr->content, ptr->type);
		printf("content: %s, type: %d\n", ((t_token *) ptr->content)->string, ((t_token *) ptr->content)->type);
        ptr = ptr->next;
    }
}

int	get_quote_status(char *input, int i, int status)
{
	if (status == N_QUOTE && input[i] == '\'')
		return (IN_SQUOTE);
	if (status == N_QUOTE && input[i] == '\"')
		return (IN_DQUOTE);
	if (status == IN_SQUOTE && input[i] == '\'')
		return (N_QUOTE);
	if (status == IN_DQUOTE && input[i] == '\"')
		return (N_QUOTE);
	return (status);
}

int	token_type(char *input, int i)
{
	if (ft_isspace(input[i]))
		return (SPACE);
	if (input[i] == '|')
		return (PIPE);
	if (input[i] == '<' && input[i + 1] == '<')
		return (HERE_DOC);
	if (input[i] == '>' && input[i + 1] == '>')
		return (OUTPUT_APP);
	if (input[i] == '<')
		return (INPUT);
	if (input[i] == '>')
		return (OUTPUT_TRUNC);
	if (input[i] == '\0')
		return (NULL_CHAR);
	return (0);
}

t_list	*token_elem(t_token *token, char *input, int start, int type)
{
	char *str_content;

    printf("token start index: %d, start char: %c ,len: %d\n", token->start_index, input[token->start_index], token->len);
    str_content = ft_substr(input, start, token->len);
	/* if (!str_content)
		return (NULL); */
	token->string = str_content;
	token->type = type;
    printf("token struct's str content: %s, type: %d\n", token->string, token->type);
	return (ft_lstnew(token));
}

int	save_token(char *input, int i, t_token *token, t_list **tokens_lst)
{
	int		type;
	t_list	*new_elem;

	type = token_type(input, i);
    new_elem = NULL;
	if (type != 0)
	{
		if (i && token_type(input, i - 1) == 0)
		{
            token->len = i - token->start_index;
            new_elem = token_elem(token, input, token->start_index, WORD);
            ft_lstadd_back(tokens_lst, new_elem);
            printf("save_token:\n");
            print_list(*tokens_lst);
            //printf("content: %s, type: %d\n", ((t_token *) tokens_lst->content)->string, ((t_token *) tokens_lst->content)->type);
        }
		else if (type != SPACE)
		{
			if (type == HERE_DOC || type == OUTPUT_APP)
				i++;
            token->len = i - token->start_index + 1;
            new_elem = token_elem(token, input, token->start_index, type);
            ft_lstadd_back(tokens_lst, new_elem);
            printf("save_token:\n");
            print_list(*tokens_lst);
            //printf("content: %s, type: %d\n", ((t_token *) tokens_lst->content)->string, ((t_token *) tokens_lst->content)->type);
		}
		token->start_index = i + 1;
	}
	return (token->start_index);
}

t_list	*token_lst(char *input, int size)
{
	t_list	*tokens_lst;
	t_token	*token;
	int		i;
	int		status;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	token->string = NULL;
	tokens_lst = NULL;
	i = 0;
	status = N_QUOTE;
	while (i <= size)
	{
		status = get_quote_status(input, i, status);
		if (status == N_QUOTE)
			token->start_index = save_token(input, i, token, &tokens_lst);
        //printf("In token_lst function: content: %s, type: %d\n", ((t_token *) tokens_lst->content)->string, ((t_token *) tokens_lst->content)->type);
		i++;
	}
	return (tokens_lst);	
}

/* void    print_list(t_list *list)
{
    t_list	*ptr;

	ptr = list;
	while (ptr)
    {
        //printf("content: %s, quote:	%d, type: %d\n", ptr->content, ptr->type);
		printf("content: %s, type: %d\n", ((t_token *) ptr->content)->string, ((t_token *) ptr->content)->type);
        ptr = ptr->next;
    }
}
 */
//int	main(int arc, char **arv)
int main(void)
{
	int size;
    t_list	*tokens_lst;
    char *input;

	tokens_lst = NULL;
/* 	if (arc == 2)
    {
        size = ft_strlen(arv[1]);
        tokens_lst = token_lst(arv[1], size);
        print_list(tokens_lst);
    } */
    //input = readline("minishell$  ");
    input = "echo > f";
    size = ft_strlen(input);
    tokens_lst = token_lst(input, size);
    //print_list(tokens_lst);
	return (0);
}