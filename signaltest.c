#include "libft/libft.h"
#include <readline/readline.h>
//#include <readline/history.h> //history.h identical to readline.h
#include <unistd.h>
#include <signal.h>

static int sig;

//static void	sig_handler(int signum, siginfo_t *info, void *context)
static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
	//	ft_putchar_fd('\n', 1);
	//	rl_replace_line("", 0);
	//	rl_on_new_line();
	//	rl_redisplay();
		sig = signum;
	}
}

int main(int argc, char **argv)
{
	char	*input;
	pid_t	child;
	int		status;

	(void)argc;
	(void)argv;

	ft_putstr_fd("signals test shell\n", 1);

/*  	struct sigaction	sigact;
	sigact.sa_sigaction = sig_handler;
//	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sigact, 0);
	sigaction(SIGQUIT, &sigact, 0);
 */
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);

	input = NULL;
	status = 0;
	while (1)
	{
		input = readline("input: ");

		// handle ctrl+D
		if (!input)
		{
			ft_putchar_fd('\n', 1);
			exit(0);
		}

	//	ft_printf("input was %s\n", input);

		if (ft_strlen(input) > 0)
		{
			add_history(input);

			child = fork();
			if (child == 0) 
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve(input, NULL, NULL);
			}
			else
			{
				waitpid(child, &status, 0);
				if (status)
					status += 128;/// ?????
				ft_printf("%s exited with status %d\n", input, status);
			}
			free(input);
		}
	}
	return (1);
}