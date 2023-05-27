# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 20:37:43 by jhenriks          #+#    #+#              #
#    Updated: 2023/05/27 19:35:18 by jhenriks         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar

CFLAGS += -Wall -Wextra -Werror -g3

NAME = minishell
SRC = src/minishell.c src/utils.c src/debug.c src/fs_utils.c
SRC += src/env/env_parsing.c src/env/env_cleanup.c src/env/env_utils.c src/env/env_export.c src/env/env_debug.c
SRC += src/lexer/lexer.c src/lexer/lexer_utils.c src/lexer/lexer_token_utils.c
SRC += src/expand/expand.c src/expand/expand_false_var.c src/expand/expand_quotes.c src/expand/expand_exit_status.c
SRC += src/parser/parser_commands.c src/parser/parser_commands_utils.c src/parser/parser_utils.c src/parser/parser_redirects.c
SRC += src/builtin/cd.c src/builtin/echo.c src/builtin/env.c src/builtin/exit.c src/builtin/export.c src/builtin/pwd.c src/builtin/unset.c
SRC += src/signal/signal.c
SRC += src/exec/exec.c src/exec/exec_utils.c
OBJ = $(SRC:.c=.o)
HEADERS = include/minishell.h

HEADER_PATH = ./include
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -Llibft -lft
LIBS += -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -lreadline

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I ~/.brew/opt/readline/include -I $(HEADER_PATH) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ) : $(HEADERS)

$(LIBFT) :
	make -C $(LIBFT_PATH)

clean :
	rm -f $(OBJ)
	make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all
