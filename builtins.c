#include "libft/libft.h"
#include <readline/readline.h>
//#include <readline/history.h> //history.h identical to readline.h
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <limits.h>
#ifndef PATH_MAX
# define PATH_MAX 4096
#endif




// Helper function for getting current absolute directory path, without the ending slash
// Returns pointer to the path as string, or NULL in case of error
char	*get_curr_dir()
{
	char	*buf;
	char	*dir;

	buf = NULL;
	dir = NULL;
	buf = (char *)malloc(PATH_MAX);
	if (buf)
	{
		dir = getcwd(buf, PATH_MAX);
		free(buf);
	}
	return (dir);
}

// helper that expands relative path to abolute
// intended for cd builtin, until I realized it's not needed
// may be useful in other places
char	*get_full_path(const char *path)
{
	int		len;
	char	*full_path;
	char	*curr_dir;

	curr_dir = get_curr_dir();
	len = ft_strlen(curr_dir) + ft_strlen(path) + 2;
	full_path = (char *)malloc(sizeof(char) * len);
	ft_bzero(full_path, len);
	ft_strlcat(full_path, curr_dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, path, len);
	return(full_path);
}

// helper that checks whether the path is directory
// could be useful add to libft?
int	ft_is_dir(const char *path)
{
	struct stat stat_buf;

	if (stat(path, &stat_buf) != 0)
		return (0);
	return S_ISDIR(stat_buf.st_mode);
}





// exit builtin
void	exit_shell(char *n)
{
	int	status;

	status = 0;
	ft_putstr_fd("exit\n", 1);
	if (n)
	{
		if (!ft_isnumstr(n))
		{
			ft_printf("exit: %s: numeric argument required\n", n);//FIXME to STDERR
			exit(255);
		}
		status = (unsigned char)ft_atoi(n);
	}
	exit(status);
}

// pwd builtin
int	pwd()
{
	ft_putstr_fd(get_curr_dir(), 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

// cd builtin
// If no path is given, and $HOME environment variable is set, chdir to $HOME
// If no path is given, and $HOME is not set, do nothing (untested)
//
//TODO
// - make sure it works with path that have spaces, or other special characters
// - make sure PWD and OLDPWD environment variable is updated
// - should $HOME get pulled with getenv(), or do we have own environment within the shell??
// - errors should be output to STDERR, so no ft_printf
int	cd(char *path)
{
	char	*home_dir;

	if (path && *path)//checking *path probably not necessary after lexer parsing
	{
		if (access(path, F_OK) < 0)
			ft_printf("cd: no such file or directory: %s\n", path);
		else if (access(path, X_OK) < 0)
			ft_printf("cd: permission denied: %s\n", path);
		else if (!ft_is_dir(path))
			ft_printf("cd: not a directory: %s\n", path);
		else
			if (chdir(path) == 0)
				return (0);
	}
	else
	{
		home_dir = getenv("HOME");// get from minishell's "own" environment?????
		if (home_dir)
			if (chdir(home_dir) == 0)
				return (0);
	}
	return (1);
}

// echo builtin
int	echo(char **str)
{
	int	n;

	n = 0;
	if (*str)
	{
		if (!ft_strncmp("-n", *str, 3))
		{
			n = 1;
			str++;
		}
		while (*str)
		{
			ft_putstr_fd(*str, 1);
			str++;
			if (*str)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}





// parses environment from main's **envp argument into linked list,
// that has the env variable stored as 2D array from ft_split
// NOTE: Rememver to free the 2D array when not needed!
//
// FIXME: things would get odd if some environment variable
// has a '=' character in its value, which is possible although unlikely.
// May need more elegant parser than ft_split, or some solution for
// merging the splitted value.
void	parse_env(t_list **env_list, char **envp)
{
	t_list	*new;

	while (*envp)
	{
		new = ft_lstnew(ft_split(*envp, '='));
		ft_lstadd_back(env_list, new);
		envp++;
	}
}


int	print_env(t_list *env_list)
{
	char **envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
	//	ft_printf("%s=%s\n", (char *)env_list->content[0], (char *)env_list->content[1]);
		ft_printf("%s=%s\n", envvar[0], envvar[1]);
		if (env_list->next)
			print_env(env_list->next);
	}
	else
	{
		ft_printf("%s\n", NULL);// wat to do here  ????
	}
	return (0);
}



int main(int argc, char **argv, char **envp)
{
	char	*input;
//	pid_t	child;
	int		status;
	char	*command;
	t_list	*env_list;

	(void)argc;
	(void)argv;
//	(void)envp;
	
	ft_putstr_fd("builtins test shell\n", 1);

	input = NULL;
	status = 0;
	command = NULL;
	env_list = NULL;


	parse_env(&env_list, envp);
//	print_env(env_list);


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

			command = "exit";
			if (!ft_strncmp(command, input, ft_strlen(command)))
			{
				if (ft_strlen(input) == ft_strlen(command))
					exit_shell(NULL);
				else
					exit_shell(input + 5);
			}

			command = "pwd";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				pwd();

			command = "cd";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				cd(input + 3);

			command = "echo";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				echo(ft_split(input + 5, ' '));

			command = "env";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				print_env(env_list);

		}
		free(input);
	}
	return (1);
}