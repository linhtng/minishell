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

void	launch_prompt(char *input, char **envp)
{
	t_list	*tokens;
	t_list	*env_list;
	t_list	*cmds;

	tokens = NULL;
	env_list = NULL;
	cmds = NULL;
	parse_env(&env_list, envp);
	setup_signals();
	input = readline("minishell$  ");
	while (input != NULL && ft_strncmp(input, "exit", 5))
	{
		if (ft_strlen(input) > 0)
			add_history(input);
		if (lexer(input, &tokens))
		{
			if (expand(&tokens, &env_list))
				print_tokens_list(tokens);
			if (parse_commands(&tokens, &cmds))
			{
				printf("Command list:\n");
				print_cmd_list(cmds);
			}
		}
		ft_lstclear(&tokens, del_token);
		ft_lstclear(&cmds, del_cmds);
		free(input);
		input = readline("minishell$  ");
	}
	if (input)
		free(input);
	clear_env_list(&env_list);
}

int	main(int arc, char **arv, char **envp)
{
	char	*input;

	input = NULL;
	if (arc == 1 && arv)
		launch_prompt(input, envp);
	return (1);
}
