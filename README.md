<h1 align="center">
	🐚 minishell 
</h1>
<p align="center">
	<b><i>As beautiful as a shell🐚</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/linhtng/minishell?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/linhtng/minishell?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/linhtng/minishell?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/linhtng/minishell?color=green" />
</p>

---

## Introduction

This project was all about recreating your very own (mini)shell, taking bash as reference. This was a pair-coding project, and I was honored to do it with [@jnsh](https://github.com/jnsh)

#### What the Shell?

The shell we are implementing works as a command interpreter communicating with the OS kernel in a secure way, and allows us to perform tasks from a command line, such as control processes and files, start and control other programs. The shell manages the interaction between you and the operating system by prompting you for input, interpreting that input for the operating system, and then handling any resulting output from the operating system.

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
	cmd 0:
		pathname: echo
		argv: {echo, hello  expandedUser, NULL}
		read_fd: STDIN_FILENO
		write_fd: pipe0[1]
	cmd 1:
		pathname: grep
		argv: {grep, h, NULL}
		read_fd: pipe0[0] (read output of previous command)
		write_fd: pipe1[1]
	cmd 2:
		pathname: cat
		argv: {cat, NULL}
		read_fd: pipe1[0]
		write_fd: pipe2[1]
	cmd 3:
		pathname: cat
		argv: {cat, NULL}
		read_fd: pipe2[0]
		write_fd: pipe3[1]
	cmd 4:
		pathname: echo
		argv: {echo, done   expandedUser, NULL}
		read_fd: pipe3[0]
		write_fd: STDOUT_FILENO
```

### Executor
With all our data properly on our structs, the ``executor`` has all the necessary information to execute commands. For this part we use separate processess to execute either our builtins or other commands inside child processes that redirect ``stdin`` and ``stdout`` just like on pipex.

In cases of error, we must return the correct [exit code](https://tldp.org/LDP/abs/html/exitcodes.html).

### Built-in commands
- `echo` prints arguments followed by newline, with option `-n` prints arguments without a newline
- `cd` changes current directory to relative or absolute path passed as an argument
- `pwd` prints full path of the current directory
- `export` sets an environment variable passed as an argument, with no arguments it usually prints list of exported variables similar to `env`
- `unset` remove environment variable passed as an argument
- `env` prints list of exported environment variables
- `exit` exits the shell, it accepts number between 0-255 as an ergument that specifies the exit status code.

### Control characters (Ctrl + key)

The `Ctrl-C` and `Ctrl-\` key inputs can be detected by listening to `SIGINT` and `SIGQUIT` signals from terminal. Detecting `Ctrl-D` is to simply check if input is NULL.

##### When prompt is active:
`Ctrl-C` should display empty prompt in a new line

`Ctrl-D` exits the shell

`Ctrl-\` does nothing

##### When subprocess is running:
`Ctrl-C` sends SIGINT to the subprocess, exit code should be `130`

`Ctrl-D` sends EOF marker to the subprocess (there is no UNIX signal for this, but sending EOT character to the subprocess via STDIN seems to be enough: https://askubuntu.com/questions/724990/what-is-eof-and-how-to-trigger-it)

`Ctrl-\` sends SIGQUIT to the subprocess, exit code should be `131`

## Installation
### Clone the repository and run minishell:
``` 
git clone https://github.com/linhtng/minishell.git
cd minishell
make
./minishell
```
As this project is made to mimic bash, you can try any commands you normally would try in bash, except for the ones using ";" or "\".

## Summary

This is my first pair-coding project, which for me was an amazing experience. What I think we did well was dividing up the different parts of the project while also supporting each other when we ran into issues, and we documented our progress after each working day. I learnt a lot about collaborating using Github and communication with teammate in general. IMO, the hardest part of this project was handling all the edge cases, which keep coming to you once you closed your eyes ready to go to bed 😂 It took us 2 retries to pass this project, but we certainly learn a lot while having fun and achieving shell-growth! I mean self-growth! Ok, I'll see myself out.

<img width="241" alt="image" src="https://github.com/linhtng/minishell/blob/master/Brain%20Before%20Sleep%20Meme.png">

## References
* [minishell - 42 Docs](https://harm-smits.github.io/42docs/projects/minishell)
* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
* [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
