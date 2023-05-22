/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:07 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/22 19:25:55 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdarg.h>
# include "libft.h"

enum	e_token_types
{
	WORD,
	SPACE,
	VAR,
	NULL_CHAR,
	PIPE,
	HERE_DOC,
	OUTPUT_APP,
	INPUT,
	OUTPUT_TRUNC,
};

enum	e_quote
{
	N_QUOTE,
	IN_SQUOTE,
	IN_DQUOTE,
};

typedef struct s_token
{
	char			*string;
	int				len;
	int				start_index;
	int				type;
	int				prev_type;
}	t_token;

typedef struct s_cmd
{
	char			*pathname;
	char			**argv;
}	t_cmd;

/* utils */
void	print_error(int n, ...);
int		free_arr(char **arr);

/* lexer */
int		lexer(char *input, t_list **tokens);

/* lexer_token_utils */
int		check_var_type(t_token *token, char *str_content, int type);
int		token_prev_type(t_list **tokens);
int		unexpected_operator(t_list **tokens);
int		unexpected_newline(t_list **tokens);

/* lexer_utils */
int		get_quote_status(char *input, int i, int status);
int		token_type(char *input, int i);
void	del_token(void *content);
void	free_tokens(t_list	*tokens);

/* lexer_debug */
void	print_tokens_list(t_list *list);
void	print_cmd_list(t_list *list);

/* env_parsing */
char	**parse_variable(char *str);
void	parse_env(t_list **env_list, char **envp);

/* env_cleanup */
void	free_envvar(char **var);
void	clear_env_list(t_list **env_list);
void	del_envvar(t_list **env_list, t_list *var_node);

/* env_utils */
t_list	*find_envvar(t_list **env_list, char *var);
char	*get_envvar(t_list **env_list, char *var);
int		check_envvar_name(char *str);
int		update_envvar(t_list **env_list, char *name, char *value);

/* env_export */
void	free_env_array(char **envp);
char	**env_list_to_array(t_list *env_list);

/* env_debug */
int		print_full_env(t_list *env_list);

/* expand */
int		expand(t_list **tokens, t_list **env_list);
int		var_quote_status(char *string, int index, int q_status);

/* expand_false_var */
int		check_false_var(t_token *token, t_list **env_list);

/* expand_quotes */
int		apply_quoting_rules(t_token *token);

/* parser_commands */
int		parse_commands(t_list **token, t_list **commands);

/* parser_commands_utils */
void	del_cmds(void *content);
int		count_argv(t_list *token_lst);
int		add_argv_cmd(t_token *token, char **argv, int *i);
char	**ft_arrdup(char **src, int size);
int		ft_arrlen(char **argv);

#endif
