# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2022/11/22 15:30:31 by thuynguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g3

SRC = minishell.c \
	lexer_utils.c \
	lexer.c \
	lexer_debug.c \

OBJSFD 	= objs

OBJS 	= $(addprefix $(OBJSFD)/,$(SRC:.c=.o))

HDR 		= -I./includes

LIBFT_HDR 	= -I./includes/libft

LIBFT_BINARY = -L./includes/libft -lft

LIBFT		= ./includes/libft/libft.a

LIBS = -L/usr/lib -lreadline

all: $(LIBFT) $(NAME)

$(LIBFT):
			make -C ./includes/libft
			make bonus -C ./includes/libft

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	cc $(CFLAGS) $(HDR) $(LIBFT_HDR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) ./includes/minishell.h
	cc $(CFLAGS) $(OBJS) $(LIBFT_BINARY) $(LIBS) -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSFD)
	make -C ./includes/libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
