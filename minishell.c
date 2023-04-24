/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                           :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:01:49 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/23 19:37:54 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	launch_prompt(char *input)
{
	t_list	*tokens;

	tokens = NULL;
	input = readline("minishell$  ");
	while (input != NULL && ft_strncmp(input, "exit", 5))
	{
		if (*input)
			add_history(input);
		if (lexer(input, &tokens))
			print_tokens_list(tokens);
		ft_lstclear(&tokens, del_token);
		free(input);
		input = readline("minishell$  ");
	}
	if (!ft_strncmp(input, "exit", 5))
	{
		add_history(input);
		free(input);
	}
}

int	main(int arc, char **arv)
{
	char	*input;

	input = NULL;
	if (arc == 1 && arv)
		launch_prompt(input);
	return (0);
}
