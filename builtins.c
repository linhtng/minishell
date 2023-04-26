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


/*************** HELPERS ***************/

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
/*
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
*/

// helper that checks whether the path is directory
// could be useful add to libft?
int	ft_is_dir(const char *path)
{
	struct stat stat_buf;

	if (stat(path, &stat_buf) != 0)
		return (0);
	return S_ISDIR(stat_buf.st_mode);
}



/*************** ENV HELPERS ***************/

// helper that frees the environment variable 2D array
void	free_envvar(char **var)
{
	if (var[0])
		free(var[0]);
	if (var[1])
		free(var[1]);
	if (var)
		free(var);
}

// parses single environment variable in the form NAME[=value] into a 2D array
// FIXME too many lines
char	**parse_variable(char *str)
{
	int		nlen;
	char	**var;

	nlen = 0;
	var = (char **)malloc(2 * sizeof(char *));
	if (!var)
		return (NULL);
	while (str[nlen] != '\0' && str[nlen] != '=')
		nlen++;
	var[0] = ft_substr(str, 0, nlen);
	if (!var[0])
	{
		free(var);
		return (NULL);
	}
	if (str[nlen] == '=')
	{
		var[1] = ft_substr(str, nlen + 1, ft_strlen(str) - nlen - 1);
		if (!var[1])
		{
			free_envvar(var);
			return (NULL);
		}
	}
	else
		var[1] = NULL;
	return (var);
}
// old version that was too long and missed some malloc protects
/*char	**parse_variable(char *str)
{
	int		nlen;
	int		vlen;
	char	*ptr;
	char	**var;

	nlen = 0;
	vlen = 0;
	ptr = str;
	var = (char **)malloc(2 * sizeof(char *));
	if (!var)
		return (NULL);
	while (*ptr != '\0' && *ptr != '=')
	{
		nlen++;
		ptr++;
	}
	if (*ptr == '=')
	{
		ptr++;
		while (*ptr != '\0')
		{
			vlen++;
			ptr++;
		}
		var[0] = ft_substr(str, 0, nlen);
		var[1] = ft_substr(str, nlen + 1, vlen);
	}
	else
	{
		var[0] = ft_strdup(str);
		var[1] = NULL;
	}
	return (var);
}*/

// print full environment, including variables with no values
int	print_full_env(t_list *env_list)
{
	char **envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
	//	ft_printf("%s=%s\n", (char *)env_list->content[0], (char *)env_list->content[1]);
		if (envvar[1])
			ft_printf("%s=%s\n", envvar[0], envvar[1]);
		else
			ft_printf("%s\n", envvar[0]);
		if (env_list->next)
			print_full_env(env_list->next);
	}
	else
	{
		//empty environment FIXME remove????
		ft_printf("%s\n", NULL);
	}
	return (0);
}

// helper to find env variable with name *var from **env_list
// returns pointer to the variable's list node if one is found
// otherwise returns NULL
t_list	*find_envvar(t_list **env_list, char *var)
{
	t_list	*lst;
	char	**envvar;

	if (!env_list || !*env_list)
		return (NULL);
	lst = *env_list;
	envvar = (char **)lst->content;
	while (lst && ft_strncmp(envvar[0], var, ft_strlen(var) + 1))
	{
		lst = lst->next;
		if (lst)
			envvar = (char **)lst->content;
	}
	return (lst);
}

// helper to delete environment variable from the list
void	del_envvar(t_list **env_list, t_list *var_node)
{
	t_list	*lst;
	t_list	*prev;

	lst = *env_list;
	prev = NULL;
	while (lst)
	{
		if (lst == var_node)
		{
			if (prev)
				prev->next = lst->next;
			else
				*env_list = (*env_list)->next;
			free_envvar((char **)var_node->content);
			free(var_node);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

// clears the whole env list
void	clear_env_list(t_list **env_list)
{
	t_list	*lst;

	lst = *env_list;
	while(lst)
	{
		free_envvar((char **)lst->content);
		free(lst);
		lst = lst->next;
	}
}

// update env variable name with value 
// if variable does not exit in the environment, it will be added
// returns 0 on failure, 1 otherwise
int	update_envvar(t_list **env_list, char *name, char *value)
{
	char **var;
	t_list	*var_node;

	if (!env_list || !name || !value)
		return (0);
	var = (char **)malloc(2 * sizeof(char *));
	if (!var)
		return (0);
	var[0] = ft_strdup(name);
	var[1] = ft_strdup(value);
	if (!var[0] || !var[1])
	{
		free_envvar(var);
		return (0);
	}
	var_node = find_envvar(env_list, var[0]);
	if (var_node)
		del_envvar(env_list, var_node);
	ft_lstadd_back(env_list, ft_lstnew(var));
	return (1);
}

// getenv() replacement
char	*get_envvar(t_list **env_list, char *var)
{
	char	**envvar;

	envvar = (char **)find_envvar(env_list, var)->content;
	return (envvar[1]);
}

// parses environment from main's **envp argument into linked list,
// that has the env variable stored as 2D array from ft_split
// does not parse $_ or $OLDPWD
// NOTE: Rememver to free the 2D array when not needed!
void	parse_env(t_list **env_list, char **envp)
{
	char **var;

	while (*envp)
	{
		var = parse_variable(*envp);
		if (!var)
		{
			clear_env_list(env_list);
			exit(1);// TODO print error in case of env parsing failure?????
		}
		if (!ft_strncmp(var[0], "_", 2) || !ft_strncmp(var[0], "OLDPWD", 7))
			free_envvar(var);
		else
			ft_lstadd_back(env_list, ft_lstnew(var));
		envp++;
	}
}

// helper to free array generated with env_list_to_array
void	free_env_array(char **envp)
{
	char	**ptr;

	ptr = envp;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(envp);
}

// convert env list to array to pass it to subprocesses via **envp argument
// NOTE: remember to free the list after sybprocesses finish with free_env_array
// FIXME too many lines
char	**env_list_to_array(t_list *env_list)
{
	char	**envp;
	char	**envptr;
	char	**envvar;
	size_t	len;

	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(env_list) + 1));
	if (!envp)
		return (NULL);
	envptr = envp;
	while(env_list)
	{
		envvar = (char **)env_list->content;
		len = ft_strlen(envvar[0]) + ft_strlen(envvar[1]) + 2;
		*envptr = (char *)malloc(sizeof(char) * len);
		if (!*envptr)
		{
			free_env_array(envp);
			return (NULL);
		}
		ft_strlcat(*envptr, envvar[0], len);
		ft_strlcat(*envptr, "=", len);
		ft_strlcat(*envptr, envvar[1], len);
		env_list = env_list->next;
		envptr++;
	}
	return (envp);
}

int	check_envvar_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
			return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}


/*************** BUILTINS ***************/

// exit builtin
// NOTE: only takes first element from argument array
void	exit_shell(char *n)
{
	int	status;

	status = 0;
//	clear_env_list(env_list);//TODO needs env_list from somewhere
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


// static helper for cd builtin function
int	change_dir(t_list **env_list, char *path)
{
	char	*old_path;

	old_path = get_curr_dir();
	if (access(path, F_OK) < 0)
		ft_printf("cd: no such file or directory: %s\n", path);
	else if (access(path, X_OK) < 0)
		ft_printf("cd: permission denied: %s\n", path);
	else if (!ft_is_dir(path))
		ft_printf("cd: not a directory: %s\n", path);
	else if (chdir(path) == 0)
	{
		update_envvar(env_list, "OLDPWD", old_path);
		update_envvar(env_list, "PWD", get_curr_dir());
		return (1);
	}
	return (0);
}
// cd builtin
// NOTE: only takes first element from argument array
//
// If no path is given, and $HOME environment variable is set, chdir to $HOME
// If no path is given, and $HOME is not set, do nothing (untested)
//
//TODO
// - make sure it works with path that have spaces, or other special characters
// - errors should be output to STDERR, so no ft_printf
int	cd(t_list **env_list, char *path)
{
	char	*home_dir;

	if (path && *path)//checking *path probably not necessary after lexer parsing
	{
		if (change_dir(env_list, path))
			return (0);
	}
	else
	{
		home_dir = get_envvar(env_list, "HOME");
		if (home_dir)
			if (change_dir(env_list, home_dir))
				return (0);
	}
	ft_printf("generic error message bc cd failed\n");//FIXME
	return (1);
}

// echo builtin
int	echo(char **args)
{
	int	n;

	n = 0;
	if (*args)
	{
		if (!ft_strncmp("-n", *args, 3))
		{
			n = 1;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args, 1);
			args++;
			if (*args)
				ft_putchar_fd(' ', 1);
		}
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (0);
}

// env builtin
int	print_env(t_list *env_list)
{
	char **envvar;

	if (env_list)
	{
		envvar = (char **)env_list->content;
		if (envvar[1])
			ft_printf("%s=%s\n", envvar[0], envvar[1]);
		if (env_list->next)
			print_env(env_list->next);
	}
	return (0);
}

// export builtin
// TODO print_full_env if no arguments given???
int	export(t_list **env_list, char **args)
{
	int		retval;
	char	**var;
	t_list	*var_node;

	retval = 0;
	while (env_list && *env_list && *args)
	{
		var = parse_variable(*args);
		if (!var)
			return (1);
		if (!check_envvar_name(var[0]))
		{
			ft_printf("export: '%s': not a valid identifier\n", *args);
			args++;
			retval = 1;
			continue ;
		}
		var_node = find_envvar(env_list, var[0]);
		if (var_node && var[1])
			del_envvar(env_list, var_node);
		if (!var_node || (var_node && var[1]))
			ft_lstadd_back(env_list, ft_lstnew(var));
		args++;
	}
	return (retval);
}

// unset builtin
int	unset(t_list **env_list, char **args)
{
	int		retval;
	t_list	*var_node;

	retval = 0;
	while (env_list && *env_list && *args)
	{
		if (!check_envvar_name(*args))
		{
			ft_printf("export: '%s': not a valid identifier\n", *args);
			retval = 1;
			args++;
			continue ;
		}
		var_node = find_envvar(env_list, *args);
		if (var_node)
			del_envvar(env_list, var_node);
		args++;
	}
	return (retval);
}



// TODO
// - proper error message handling




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
//	print_full_env(env_list);

	// env_list_to_array tester
/*	char **e = env_list_to_array(env_list);
	char **p = e;
	while (*p)
	{
		ft_printf("%s\n", *p);
		p++;
	}
	free_env_array(e);
*/

	while (1)
	{
		input = readline("input: ");

		// handle ctrl+D
		if (!input)
		{
			ft_putchar_fd('\n', 1);
			clear_env_list(&env_list);
			exit(0);
		}

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
				cd(&env_list, input + 3);

			command = "echo";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				echo(ft_split(input + 5, ' '));

			command = "env";
			if (!ft_strncmp(command, input, ft_strlen(command)))
				print_full_env(env_list);
			//	print_env(env_list);
			
			command = "export";
			if (!ft_strncmp(command, input, ft_strlen(command)))
			{
				char **args = ft_split(input + 7, ' ');
				export(&env_list, args);
				free(args[0]);
				if (args[1])
					free(args[1]);
				free(args);
			}

			command = "unset";
			if (!ft_strncmp(command, input, ft_strlen(command)))
			{
				char **args = ft_split(input + 6, ' ');
				unset(&env_list, args);
				free(args[0]);
				if (args[1])
					free(args[1]);
				free(args);
			}

		}
		free(input);
	}
	return (1);
}