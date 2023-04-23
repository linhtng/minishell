/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:53:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/23 19:46:47 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	add_token_lst(t_token *token, char *input, int type, t_list **tokens)
{
	char	*str_content;
	t_token	*new_token;

	str_content = ft_substr(input, token->start_index, token->len);
	if (str_content)
	{
		new_token = (t_token *) malloc(sizeof(t_token));
		if (new_token)
		{
			new_token->string = str_content;
			new_token->type = type;
			new_token->start_index = token->start_index;
			new_token->len = token->start_index;
			ft_lstadd_back(tokens, ft_lstnew(new_token));
		}
	}
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
			add_token_lst(token, input, WORD, token_lst);
		}
		else if (type != SPACE && type != NULL_CHAR)
		{
			if (type == HERE_DOC || type == OUTPUT_APP)
				(*i)++;
			token->len = *i - token->start_index + 1;
			add_token_lst(token, input, type, token_lst);
		}
		token->start_index = *i + 1;
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
			token->start_index = save_token(input, &i, token, &tokens_lst);
		i++;
	}
	free(token);
	return (tokens_lst);
}

int	lexer(char *input, t_list **tokens)
{
	int	len;
	int	s_quote;
	int	d_quote;

	len = ft_strlen(input);
	s_quote = count_occurences(input, '\'');
	d_quote = count_occurences(input, '\"');
	if ((s_quote && s_quote % 2 != 0) || (d_quote && d_quote % 2 != 0))
	{
		printf("minishell$: unexpected EOF while looking for matching ");
		if (s_quote % 2 != 0)
			printf("`\'\'");
		else
			printf("`\"\'");
		printf("\nminishell$: syntax error: unexpected end of file\n");
		return (0);
	}
	*tokens = token_lst(input, len);
	if (!tokens)
		return (0);
	return (1);
}
