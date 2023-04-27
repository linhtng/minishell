/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:56:20 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/23 19:48:28 by thuynguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdarg.h>

typedef struct s_spldata
{
	size_t	i;
	int		j;
	int		start;
	int		in_quotes;
	size_t	slen;
}	t_spldata;

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

typedef struct s_sh_data
{
	char	*input;
	char	**tokens;
}	t_sh_data;

/* prompt */
void	launch_prompt(char *input);

/* lexer */
int		lexer(char *input, t_list **tokens);

/* lexer_token_utils */
int	check_var_type(t_token *token, char *str_content, int type);
int	token_prev_type(t_list **tokens);
int	unexpected_operator(t_list **tokens);
int	unexpected_newline(t_list **tokens);

/* lexer_utils */
int		count_occurences(const char *str, char c);
int		get_quote_status(char *input, int i, int status);
int		token_type(char *input, int i);
void	del_token(void *content);
void	free_tokens(t_list	*tokens);

/* minishell_utils */
void    print_error(int n, ...);

/* lexer_debug */
void	print_tokens_list(t_list *list);

#endif
