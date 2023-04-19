CFLAGS = -Wall -Wextra -Werror

builtins: builtins.c libft/libft.a
	cc $(CFLAGS) -lreadline libft/libft.a builtins.c

signal: signaltest.c libft/libft.a
	cc $(CFLAGS) -lreadline libft/libft.a signaltest.c

libft/libft.a:
	make -C libft
	make -C libft clean