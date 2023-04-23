# minishell to-do

### Display a prompt and have a working history
Seems to be as simple as:
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
We split the input string into an array of strings i.e tokens.

### Expander and quote handler

Expanding environment variables with $ followed by characters.

`$?` expands to the exit status of the most recently executed foreground pipeline.

### Parser

The parser is responsible for analyzing the command-line input and creating a data structure that represents the syntax of the input.
For us, parsing is the process of turning the 2D array of tokens into a linked list of command nodes. Each command node is a struct that consists data to pass to the executor.
For the above example `"echo "hello  $USER " > file | grep h | cat << eof | cat >> file | echo 'done   $USER'"`, command linked list could be like:
```
cmds:
	cmd 1:
		infile: 0 (default)
		outfile: pipe1[1]
		path: echo
		full_cmd: {echo, hello  $USER , NULL}
	cmd 2:
		infile: pipe1[0] (read output of previous command)
		outfile: pipe2[1]
		path: grep
		full_cmd: {grep, h, NULL}
	cmd 3:
		infile: pipe2[0] (read output of previous command)
		outfile: pipe3[1]
		path: cat
		full_cmd: {grep, <<, eof, NULL}
	cmd 4:
		infile: pipe3[0] (read output of previous command)
		outfile: fd[3] i.e. fd corresponding to the open file 'file'
		path: cat
		full_cmd: {grep, >>, file, NULL}
	cmd 5:
		infile: fd[3] (read output of previous command)
		outfile: 1
		path: echo
		full_cmd: {echo, done   $USER, NULL}
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

---
#### Progress 17.04.23
wip_0: lexer split the input lines into a 2D array of token, handle ' and "

<img width="702" alt="0417_progress" src="https://user-images.githubusercontent.com/33163654/232571562-09b20744-a786-41a4-be1b-b4822a5804c6.png">

Next step: environment variable expansion. Maybe instead of 2D array, a linked list is better to store the tokens into, so you could save the in and out of single/double quote status.

Also made some progress with handling ctrl+key combinations, but as I learned in minitalk, the unix signal handling is very messy and therefore some problems remain. Hoping to get this sorted next day, and push sample code to the repo.

#### Progress 18.04.23
Pushed signal and builtin command test shells to `wip_joonas` branch.

Signals (i.e. ctrl+key commands) still have some problems. Currently everything seems to work correctly for child processes, but on the shell prompt only Ctrl+D should work perfectly.

Implemented `exit`, `pwd` and `cd` builtins in the builtin test shell. They should work perfectly, but `cd` should still need some final touches once the minishell's environment variable handling is complete (more details in code).

#### Progress 19.04.23

In `wip_joonas`: added basic environment variable parsing from `main()`'s `**envp` argument into a linked list. Added `echo` and `env` builtins, and some tweaks to the existing builtins.

#### Progress 20.04.23

In `wip_0`: fixed the lexer's tokennization split to handle banana string like:
`echo hello he"l  l"o0 'he "l l" o1' "he"  ll"o2" "   "he"ll "o3 he "l l "o4 "" ' ' he" ll "o5 he "l l"o6 ' '`

`echo hello he"ll"o0 'he"ll"o1' "he"ll"o2" ""he"ll"o3 he"ll"o4"" ''he"ll"o5 he"ll"o6''`

Next: properly save those tokens into the linked list.

#### Progress 21.04.23

In `wip_joonas`, all builtins working. Some still require minor tweaks, noted in the code comments.
Some further work on environment variables, but it should be fully working and editable with builtin commands and the helper functions. Remaining items detailed in code comments.

#### Progress 20.04.23

In `wip_0`: lexer's tokenization working: save the tokens into t_list tokens. Handled syntax error when encounter unmatching quotes and should free memory when not needed anymore. 
