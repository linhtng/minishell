/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:07 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/27 19:36:56 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

int	g_exit_status;

enum	e_token_types
{
	WORD,
	SPACE_CHAR,
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
	int				read_fd;
	int				write_fd;
}	t_cmd;

/* utils */
void	print_error(int n, ...);
int		free_arr(char **arr);

/* fs_utils */
char	*get_curr_dir(void);
int		ft_is_dir(const char *path);

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

/* expand_false_var */
int		check_false_var(t_token *token, t_list **env_list);

/* expand_exit_status */
int		var_quote_status(char *string, int index, int q_status);
int		expand_exit_status(t_token *token);

/* expand_quotes */
int		apply_quoting_rules(t_token *token);

/* parser_commands */
int		parse_commands(t_list **token, t_list **commands);

/* parser_commands_utils */
void	del_cmds(void *content);
char	**init_argv_arr(t_list *token_lst);
int		add_argv_cmd(t_token *token, char **argv, int *i, t_list **token_ptr);
int		parse_pipe(t_list *commands, int *pipe_input);

/* parser_redirects */
int		get_redirects(t_list *token_lst, t_cmd **cmd);

/* builtins */
int		cd(t_list **env_list, char *path);
int		echo(char **args);
int		env(t_list *env_list);
int		exit_shell(t_list **env_list, char *n);
int		export(t_list **env_list, char **args);
int		pwd(void);
int		unset(t_list **env_list, char **args);

/* signals */
void	close_echoctl(struct termios *t);
void	reset_echoctl(struct termios *t);
void	ctrl_d_signal(void);
void	sigquit_child(void);

/* signals_setup */
void	setup_signals(void);
void	setup_signals_child(void);

/* exec */
void	executor(t_list	*env_list, t_list *cmd_list);

/* exec_utils */
int		cmd_is_builtin(char *path);
int		run_builtin(t_list	*env_list, char *path, char **full_cmd);
char	*expand_path(t_list *env_list, char *cmd);
void	close_redirects(int *write_fd, int *read_fd);
int		redirect_streams(int write_fd, int read_fd);

#endif
