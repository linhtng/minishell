builtins: builtins.c libft/libft.a
	cc -lreadline libft/libft.a builtins.c

signal: shelltest.c libft/libft.a
	cc -lreadline libft/libft.a shelltest.c

libft/libft.a:
	make -C libft
	make -C libft clean