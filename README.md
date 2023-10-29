# minishell
<img width="241" alt="image" src="https://github.com/linhtng/minishell/blob/master/minishellBanner.png">

## Introduction

This project is all about recreating your very own (mini)shell, taking bash as reference. This is a pair-coding project, and I was honored to do it with [@jnsh](https://github.com/jnsh)

#### What the Shell?

If we think of the OS as a nut or a seashell, the kernel/seed is the core of the nut and has to be surrounded by a cover or shell. So, the shell we are implementing works as a command interpreter communicating with the OS kernel in a secure way, and allows us to perform tasks from a command line, such as control processes and files, start and control other programs. The shell manages the interaction between you and the operating system by prompting you for input, interpreting that input for the operating system, and then handling any resulting output from the operating system.

## Implementation

As the challenge is to recreate a simple version of bash, a commonly used GNU shell, we started by learning how bash actually works with the help of [bash manual](https://www.gnu.org/software/bash/manual/bash.html) and other resources listed under References.
The general idea of ``Minishell`` is to read input from the user in a prompt using [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html), the input is then proceeded through 4 steps: `lexer` → `parser` → `expander` → `executor`.

### Display a prompt and have a working history
This is as simple as:
```
input = readline("prompt");
add_history(input);
```
The line `readline` returns is allocated with `malloc()`; you should `free()` the line when you are done with it. The line returned has the final newline removed, so only the text remains.

If `readline` encounters an EOF (Ctrl + D) while reading the line, and the line is empty at that point, then (char *)NULL is returned. Otherwise, the line is ended just as if a newline \n had been typed.

A zero-length input shoud not be added to history.

The history can be freed calling `void rl_clear_history (void)`.

### Lexer
In a shell, a lexer (short for "lexical analyzer") is a component of the shell's parser that breaks down a user's input into a series of tokens or lexemes.

The lexer takes the user's input, which is typically a string of characters, and breaks it down into a series of smaller pieces or tokens that are more easily processed by the shell's parser. For example, the lexer may break down the input `"echo "hello  $USER " > file | grep h | cat << eof | cat >> file | echo 'done $USER'"` into the following tokens:

`echo`: a command that prints its arguments to the standard output.

`"hello $USER "`: a double-quoted string that contains the string "hello " and the value of the environment variable $USER.

`>`: a redirection operator that redirects the standard output of the previous command to a file named file.

`|`: a pipe operator that connects the standard output of the previous command to the standard input of the next command.

`grep`: a command that searches for a pattern in its input and prints the matching lines to its standard output.

`h`: a string that represents the pattern to search for.

`|`: a pipe operator that connects the standard output of the previous command to the standard input of the next command.

`cat`: a command that concatenates files and prints the result to its standard output.

`<<`: a here-document operator that allows the input of multiple lines until a delimiter (eof in this case) is encountered.

`eof`: the delimiter for the here-document.

`|`: a pipe operator that connects the standard output of the previous command to the standard input of the next command.

`cat`: a command that concatenates files and prints the result to its standard output.

`>>`: a redirection operator that appends the standard output of the previous command to the end of the file named file.

`|`: a pipe operator that connects the standard output of the previous command to the standard input of the next command.

`echo`: a command that prints its arguments to the standard output.

`'done $USER'`: a single-quoted string that contains the string 'done $USER', the environment variable $USER doesn't expand within ''.

Each token corresponds to a distinct component of the user's command, such as the command name, arguments, and options.
We split the input string into a linked list of tokens.

### Expander and quote handler

Expanding environment variables with $ followed by characters.

`$?` expands to the exit status of the most recently executed foreground pipeline.

### Parser

The parser is responsible for analyzing the command-line input and creating a data structure that represents the syntax of the input.
For us, parsing is the process of turning the list of tokens into a linked list of command nodes. Each command node is a struct that consists data to pass to the executor.
- Iterate through the token list
- Whenever a redirection is found, check the type of redirection and retrieve the file descriptor(s) containing the info we need as the infile and outfile. Heredoc `<<`, if encountered, is also handled at this step by 
- If a pipe is found, set up the current process's read- and write fd to the corresponding end of the pipe. Then, add a new node to the list of commands.
- When tokens type word or type var are found, add them to the argument list (argv)

For the above example `"echo "hello  $USER " > file | grep h | cat << eof | cat >> file | echo 'done   $USER'"`, command linked list could be like:
```
cmds:
	cmd 1:
		pathname: echo
		argv: {echo, hello  $USER , NULL}
		read_fd: 0 (default)
		write_fd: pipe1[1]
	cmd 2:
		infile: pipe1[0] (read output of previous command)
		outfile: pipe2[1]
		path: grep
		argv: {grep, h, NULL}
	cmd 3:
		infile: pipe2[0] (read output of previous command)
		outfile: pipe3[1]
		path: cat
		argv: {cat, NULL}
	cmd 4:
		infile: pipe3[0] (read output of previous command)
		outfile: fd[3] i.e. fd corresponding to the open file 'file'
		path: cat
		argv: {cat, NULL}
	cmd 5:
		infile: fd[3] (read output of previous command)
		outfile: 1
		path: echo
		argv: {echo, done   $USER, NULL}
```


### Executor
With all our data properly on our structs, the ``executer`` has all the necessary information to execute commands. For this part we use separate processess to execute either our builtins or other commands inside child processes that redirect ``stdin`` and ``stdout`` just like on pipex.

In cases of error, we must return the correct exit code: https://tldp.org/LDP/abs/html/exitcodes.html

### Built-in commands
- `echo` prints arguments followed by newline, with option `-n` prints arguments without a newline
- `cd` changes current directory to relative or absolute path passed as an argument
- `pwd` prints full path of the current directory
- `export` sets an environment variable passed as an argument, with no arguments it usually prints list of exported variables similar to `env`
- `unset` remove environment variable passed as an argument
- `env` prints list of exported environment variables
- `exit` exits the shell, it accepts number between 0-255 as an ergument that specifies the exit status code.

### Control characters (Ctrl + key)

The `Ctrl-C` and `Ctrl-\` key inputs can be detected by listening to `SIGINT` and `SIGQUIT` signals from terminal. Detecting `Ctrl-D` input is still a mystery 😧

##### When prompt is active:
`Ctrl-C` should display empty prompt in a new line

`Ctrl-D` exits the shell

`Ctrl-\` does nothing

##### When subprocess is running:
`Ctrl-C` sends SIGINT to the subprocess, exit code should be `130`

`Ctrl-D` sends EOF marker to the subprocess (there is no UNIX signal for this, but sending EOT character to the subprocess via STDIN seems to be enough: https://askubuntu.com/questions/724990/what-is-eof-and-how-to-trigger-it)

`Ctrl-\` sends SIGQUIT to the subprocess, exit code should be `131`
