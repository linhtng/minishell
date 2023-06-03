/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:02:49 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/31 21:23:13 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_list **env_list, char *input)
{
	t_list	*tokens;
	t_list	*cmds;
	int		ret;

	tokens = NULL;
	cmds = NULL;
	ret = 0;
	if (lexer(input, &tokens))
	{
		expand(&tokens, env_list);
		if (parse_cmds(&tokens, &cmds, env_list))
			ret = 1;
		executor(env_list, cmds);
	}
	ft_lstclear(&tokens, del_token);
	ft_lstclear(&cmds, del_cmds);
	return (ret);
}

void	launch_prompt(char *input, char **envp)
{
	t_list			*env_list;
	struct termios	t;

	env_list = NULL;
	parse_env(&env_list, envp);
	tcgetattr(STDIN_FILENO, &t);
	while (1)
	{
		setup_signals();
		close_echoctl(&t);
		input = readline("minishell$  ");
		reset_echoctl(&t);
		if (!input)
			ctrl_d_signal();
		if (ft_strlen(input) > 0)
			add_history(input);
		if (ft_isemptystr(input))
			g_exit_status = 0;
		else if (!parsing(&env_list, input))
			g_exit_status = 1;
		free(input);
	}
	clear_env_list(&env_list);
}

int	main(int arc, char **arv, char **envp)
{
	char	*input;

	input = NULL;
	g_exit_status = 0;
	if (arc == 1 && arv)
		launch_prompt(input, envp);
	return (1);
}
