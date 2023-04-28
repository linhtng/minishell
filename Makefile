# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 20:37:43 by jhenriks          #+#    #+#              #
#    Updated: 2023/04/28 18:28:45 by jhenriks         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar

CFLAGS += -Wall -Wextra -Werror

NAME = minishell
SRC = src/minishell.c src/utils.c
SRC += src/env/env_parsing.c src/env/env_cleanup.c
OBJ = $(SRC:.c=.o)

HEADER_PATH = ./include
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

LIBS = -Llibft -lft
LIBS += -lreadline

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ) : $(SRC)

$(LIBFT) :
	make -C $(LIBFT_PATH)

clean :
	rm -f $(OBJ)
	make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all
