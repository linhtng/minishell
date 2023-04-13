/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:01:49 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/13 19:45:31 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(char *input)
{
	input = readline("minishell$  ");
	while (input != NULL && ft_strncmp(input, "exit", 5))
	{
		free(input);
		input = readline("minishell$  ");
	}
}

//int	main(int arc, char **arv, char **env)
int	main(void)
{
	char	*input;

	input = NULL;
	display_prompt(input);
	return (0);
}
