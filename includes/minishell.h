/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:56:20 by thuynguy          #+#    #+#             */
/*   Updated: 2023/04/13 18:58:23 by thuynguy         ###   ########.fr       */
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

typedef struct s_sh_data
{
	char	*input;
	char	**tokens;
}	t_sh_data;

/* prompt */
void	launch_prompt(char *input);

/* lexer */
char	**token_split(char const *s, char c);

/* lexer_spl_quote */
int		count_with_quotes(char const *s, char const c, int quotes);
char	**make_arr_quotes(char const*s, char c, int quotes);
void	do_split_with_quotes(char **arr, char const *s, char c);
int		free_arr_spl(char **arr, size_t n);

/* lexer_utils */
int	count_occurences(const char *str, char c);
void	print_arr(char **arr);

#endif
