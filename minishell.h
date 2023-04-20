/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:56:20 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/19 16:47:03 by thuynguy         ###   ########.fr       */
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
	PIPE,
	INPUT,
	OUTPUT_APP,
	HERE_DOC,
	OUTPUT_TRUNC,
	NULL_CHAR,
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
}	t_token;

typedef struct s_sh_data
{
	char	*input;
	char	**tokens;
}	t_sh_data;

/* prompt */
void	launch_prompt(char *input);

/* lexer */
char	**token_arr(char const *s, char c, int *len);

/* lexer_spl_quote */
int		count_with_quotes(char const *s, char const c, int quotes);
char	**make_arr_quotes(char const*s, char c, int quotes, int *arr_len);
void	do_split_with_quotes(char **arr, char const *s, char c);
int		free_arr_spl(char **arr, size_t n);

/* lexer_utils */
int		count_occurences(const char *str, char c);
void	print_arr(char **arr);

/* lexer_lst */
t_token	*token_lstnew(char *content);
void	token_lstadd_front(t_token **lst, t_token *new);
void	token_lstclear(t_token **lst);

#endif
