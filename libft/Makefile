# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhenriks <jhenriks@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 14:37:36 by jhenriks          #+#    #+#              #
#    Updated: 2023/05/18 16:38:20 by jhenriks         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = \
ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_numlen.c ft_unumlen.c ft_uitoa.c \
ft_hexlen.c ft_itohex.c ft_memjoin.c get_next_line.c ft_printf.c \
ft_printf_conversions.c ft_printf_utils.c ft_lstprev.c ft_lstpos.c \
ft_lstnbr.c ft_isnumstr.c ft_isintstr.c ft_intdup.c ft_atof.c ft_isfloatstr.c \
ft_isspace.c ft_strmjoin.c
OBJ = $(patsubst %.c,%.o,$(SRC))
HEADER_PATH = .

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) rus $(NAME) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -I $(HEADER_PATH) -c $(SRC)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
