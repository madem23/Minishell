# MINISHELL

minishell is a minimalistic shell implemented in C. It aims to replicate some core functionality of Unix shells, providing basic command execution, environment management, and process handling.
This project is an educational implementation, following Unix principles and designed to reinforce understanding of system programming and process management.

Features:
- Executes basic commands (e.g., ls, echo, pwd, etc.)
- Supports command chaining with pipes (|)
- Input/output redirection (>, <, >>, <<)
- Handles ctrl-C, ctrl-D and ctrl-\
- Environment variable handling (export, unset, env)
- Error handling and exit status management

Technologies:

    Language: C
    Build: Makefile

Getting Started

1. Clone the repository using:
    git clone <repository-url>
    cd minishell

2. Building the Shell

    make

3. Running the Shell

    ./minishell

To remove the compiled executable, use:

    make clean

In the minishell prompt, you can type commands just like in a regular shell:

    minishell$ ls -l
    minishell$ echo "Hello World!"
    minishell$ cat file.txt | grep 'pattern'

4. Exiting

To exit minishell, type:

    exit
