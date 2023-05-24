/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:07 by jhenriks          #+#    #+#             */
/*   Updated: 2023/05/24 18:26:23 by jhenriks         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdarg.h>
# include <sys/stat.h>
# include <limits.h>
# include "libft.h"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

int	exit_status;

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
	char			*full_cmd;
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
int		var_quote_status(char *string, int index, int q_status);

/* expand_false_var */
int		check_false_var(t_token *token, t_list **env_list);

/* expand_quotes */
int		apply_quoting_rules(t_token *token);

/* parser_commands */
int		parse_commands(t_list **token, t_list **commands);

/* parser_commands_utils */
void	del_cmds(void *content);
char	**init_argv_arr(t_list *token_lst);
int		add_argv_cmd(t_token *token, char **argv, int *i, t_list **token_ptr);
int		parse_pipe(t_list *commands);

/* parser_utils */
char	*mns_strjoin(char *s1, char const *s2);

/* builtins */
int		cd(t_list **env_list, char *path);
int		echo(char **args);
int		env(t_list *env_list);
int		exit_shell(t_list **env_list, char *n);
int		export(t_list **env_list, char **args);
int		pwd(void);
int		unset(t_list **env_list, char **args);

#endif
