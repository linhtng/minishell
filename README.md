# minishell
<img width="241" alt="image" src="https://github.com/linhtng/minishell/blob/master/minishellBanner.png">

## Introduction

This project is all about recreating your very own (mini)shell, taking bash as reference. This is a pair-coding project, and I was honored to do it with [@jnsh](https://github.com/jnsh)

#### What the Shell?

If we think of the OS as a nut or a seashell, the kernel/seed is the core of the nut and has to be surrounded by a cover or shell. So, the shell we are implementing works as a command interpreter communicating with the OS kernel in a secure way, and allows us to perform tasks from a command line, such as control processes and files, start and control other programs. The shell manages the interaction between you and the operating system by prompting you for input, interpreting that input for the operating system, and then handling any resulting output from the operating system.

## Our Implementation of Minishell

``Minishell`` involves heavy parsing of the string read by [readline](https://www.man7.org/linux/man-pages/man3/readline.3.html). The code of the project is divided into different parts: the ``lexer``, the ``expander``, the ``parser``, and the ``executor``.
