/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:53:43 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/24 19:51:07 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_var_type(t_token *token, char *str_content, int type)
{
	int		status;
	int		i;

	if (!ft_strchr(str_content, '$') || token->prev_type == HERE_DOC)
		return (type);
	i = 0;
	status = N_QUOTE;
	while (str_content[i] != '$')
	{
		status = get_quote_status(str_content, i, status);
		i++;
	}
	if (status == IN_SQUOTE)
		return (type);
	return (VAR);
}

int	token_prev_type(t_list **tokens)
{
	t_list	*last_token;

	last_token = ft_lstlast(*tokens);
	if (last_token)
		return (((t_token *) last_token->content)->type);
	return (0);
}

int	add_token_lst(t_token *token, char *input, int type, t_list **tokens)
{
	char	*str_content;
	t_token	*new_token;
	t_list	*new_elem;

	new_elem = NULL;
	str_content = ft_substr(input, token->start_index, token->len);
	if (str_content)
	{
		new_token = (t_token *) malloc(sizeof(t_token));
		if (new_token)
		{
			new_token->string = str_content;
			new_token->prev_type = token_prev_type(tokens);
			new_token->type = check_var_type(new_token, str_content, type);
			new_token->start_index = token->start_index;
			new_token->len = token->start_index;
			new_elem = ft_lstnew(new_token);
			if (new_elem)
			{
				ft_lstadd_back(tokens, new_elem);
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
	token_lst(input, len, tokens);
	if (!tokens)
		return (0);
	return (1);
}
