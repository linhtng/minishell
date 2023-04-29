/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:57:07 by jhenriks          #+#    #+#             */
/*   Updated: 2023/04/29 21:00:19 by jhenriks         ###   ########.fr       */
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

/* utils */
void	print_error(int n, ...);

/* lexer */
int		lexer(char *input, t_list **tokens);

/* lexer_token_utils */
int		check_var_type(t_token *token, char *str_content, int type);
int		token_prev_type(t_list **tokens);
int		unexpected_operator(t_list **tokens);
int		unexpected_newline(t_list **tokens);

/* lexer_utils */
int		count_occurences(const char *str, char c);
int		get_quote_status(char *input, int i, int status);
int		token_type(char *input, int i);
void	del_token(void *content);
void	free_tokens(t_list	*tokens);

/* lexer_debug */
void	print_tokens_list(t_list *list);

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

#endif
