# minishell to-do

### Display a prompt and have a working history
Typing...

### Lexer
In a shell, a lexer (short for "lexical analyzer") is a component of the shell's parser that breaks down a user's input into a series of tokens or lexemes.

The lexer takes the user's input, which is typically a string of characters, and breaks it down into a series of smaller pieces or tokens that are more easily processed by the shell's parser. For example, the lexer may break down the input "ls -l /usr/bin" into the following tokens:

Token 1: "ls"

Token 2: "-l"

Token 3: "/usr/bin"

Each token corresponds to a distinct component of the user's command, such as the command name, arguments, and options.
We split the input string into an array of strings i.e tokens.

### Expander and quote handler

Expanding environment variables with $ followed by characters.

`$?` expands to the exit status of the most recently executed foreground pipeline.

### Parser

The parser is responsible for analyzing the command-line input and creating a data structure that represents the syntax of the input.
For us, parsing is the process of turning the 2D array of tokens into a linked list of command nodes. Each command node is a struct that consists data to pass to the executor.
Data needed:
```
command
path
args
input_fd
output_fd
pid

```

### Executor
With all our data properly on our structs, the ``executer`` has all the necessary information to execute commands. For this part we use separate processess to execute either our builtins or other commands inside child processes that redirect ``stdin`` and ``stdout`` just like on pipex.
