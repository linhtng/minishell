/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:02:49 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/28 20:45:36 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_list	*env_list;

	(void)argc;
	(void)argv;
	parse_env(&env_list, envp);
	ft_putstr_fd("Welcome to Minishell\n", 1);
	while ("minishell")
	{
		input = readline("input: ");
		if (!input)
		{
			ft_putchar_fd('\n', 1);
			clear_env_list(&env_list);
			exit(0);
		}
		if (ft_strlen(input) > 0)
		{
			add_history(input);
		}
		free(input);
	}
	return (1);
}
