/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:59:10 by thuynguy          #+#    #+#             */
/*   Updated: 2023/05/04 19:44:10 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_var_type(t_token *token, char *str, int type)
{
	char	*var;

	var = ft_strchr(str, '$');
	if (!var || token->prev_type == HERE_DOC)
		return (type);
	else
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

/* Minishell print syntax error near unexpected token `operator' when:
	- command line starts with pipe operator '|'
	- encounters consecutive operators
*/

int	unexpected_operator(t_list **tokens)
{
	t_list	*ptr;
	int		prev_type;
	int		type;

	ptr = *tokens;
	prev_type = 0;
	type = ((t_token *) ptr->content)->type;
	while (ptr != NULL)
	{
		prev_type = ((t_token *) ptr->content)->prev_type;
		type = ((t_token *) ptr->content)->type;
		if (prev_type >= PIPE && type >= PIPE)
		{
			print_error(3, "syntax error near unexpected token `",
				((t_token *) ptr->content)->string, "'");
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

/* Minishell print syntax error near unexpected token `newline' when:
	command line ends with an operator
*/

int	unexpected_newline(t_list **tokens)
{
	t_list	*last_token;

	last_token = ft_lstlast(*tokens);
	if (last_token)
	{
		if (((t_token *) last_token->content)->type >= PIPE)
		{
			print_error(1, "syntax error near unexpected token `newline'");
			return (1);
		}
	}
	return (0);
}
