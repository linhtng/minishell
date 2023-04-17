/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                           :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:01:49 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/13 19:45:31 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexer(char *input)
{
	char	**tokens;

	tokens = token_split(input, ' ');
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	launch_prompt(char *input)
{
	char	**tokens;

	tokens = NULL;
	input = readline("minishell$  ");
	while (input != NULL && ft_strncmp(input, "exit", 5))
	{
		if (*input)
			add_history(input);
		tokens = lexer(input);
		free(input);
		print_arr(tokens);
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
