builtins: builtins.c libft/libft.a
	cc -lreadline libft/libft.a builtins.c

signal: signaltest.c libft/libft.a
	cc -lreadline libft/libft.a signaltest.c

libft/libft.a:
	make -C libft
	make -C libft clean