*This project has been created as part of the 42 curriculum by lpons and hammar.*

## Description

Minishell is a minimalist Unix shell implementation written in C that replicates the core functionality of bash. The project serves as an introduction to process management, file descriptors, and command-line interfaces. It handles command parsing, execution, built-in commands, redirections, pipes, environment variable expansion, and signal handling.

The goal of this project is to create a functional shell that can execute commands, manage processes, handle input/output redirections, and provide a smooth interactive experience similar to bash.

## Features

- **Interactive prompt** with command history (using readline)
- **Command execution** with PATH resolution
- **Built-in commands**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes** (`|`) for chaining commands
- **Redirections**: 
  - Input redirection (`<`)
  - Output redirection (`>`)
  - Append mode (`>>`)
  - Here-document (`<<`)
- **Environment variables** expansion with `$` syntax
- **Exit status** tracking with `$?`
- **Quote handling**: Single quotes (`'`) and double quotes (`"`)
- **Signal handling**: `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`

## Instructions

### Prerequisites

- GCC or Clang compiler
- GNU Make
- Readline library

Install readline on Linux:
```bash
sudo apt-get install libreadline-dev
```

### Compilation

Clone the repository and compile the project:
```bash
git clone <repository-url>
cd Minishell
make
```

This will compile the project and generate the `minishell` executable.

### Execution

Run the shell:
```bash
./minishell
```

You will see the prompt:
```
minishell$
```

### Usage Examples

Basic command execution:
```bash
minishell$ ls -la
minishell$ echo "Hello, World!"
minishell$ pwd
```

Using pipes:
```bash
minishell$ ls -l | grep minishell
minishell$ cat file.txt | grep pattern | wc -l
```

Redirections:
```bash
minishell$ echo "test" > output.txt
minishell$ cat < input.txt
minishell$ ls -la >> log.txt
```

Here-document:
```bash
minishell$ cat << EOF
> line 1
> line 2
> EOF
```

Environment variables:
```bash
minishell$ echo $PATH
minishell$ export MY_VAR=value
minishell$ echo $MY_VAR
```

Exit status:
```bash
minishell$ ls
minishell$ echo $?
0
```

### Cleaning

Remove object files:
```bash
make clean
```

Remove executable and object files:
```bash
make fclean
```

Recompile everything:
```bash
make re
```

## Project Structure

```
minishell/
├── include/
│   └── minishell.h          # Main header file with structures and prototypes
├── src/
│   ├── main.c               # Main entry point and shell loop
│   ├── init.c               # Shell initialization
│   ├── cleanup.c            # Memory cleanup
│   ├── signal_stuff.c       # Signal handling
│   ├── lexer/               # Tokenization and lexical analysis
│   │   ├── tokenizer.c
│   │   ├── token_utils.c
│   │   ├── quote_tokens.c
│   │   └── word_builder.c
│   ├── parser/              # Command parsing and syntax validation
│   │   ├── parser.c
│   │   ├── parser_utils.c
│   │   ├── syntax_validator.c
│   │   ├── pipline_parsing.c
│   │   ├── redirection_parsing.c
│   │   ├── pipe_redirect_validation.c
│   │   └── debug_print.c
│   └── exec/                # Command execution and built-ins
│       ├── exec.c
│       ├── builtins.c
│       ├── builtins2.c
│       ├── builtins3.c
│       ├── env_stuff.c
│       ├── directio.c
│       ├── here_doc_stuff.c
│       └── utils.c
├── libft/                   # Custom C library
├── Makefile                 # Build configuration
└── README.md               # This file
```

## Technical Choices

- **Lexer-Parser-Executor Architecture**: The shell is structured in three main phases:
  1. **Lexer**: Tokenizes the input string into meaningful units (words, operators, quotes)
  2. **Parser**: Builds a command structure from tokens, handling pipes and redirections
  3. **Executor**: Executes the parsed commands with proper process management

- **Token-based parsing**: Input is first tokenized to handle quotes and special characters properly
- **Quote type tracking**: Maintains quote context throughout tokenization for proper expansion behavior
- **Linked list structures**: Commands and tokens are stored in linked lists for flexible manipulation
- **Environment variable linked list**: Environment is maintained as a custom linked list for easier manipulation

## Resources

### Documentation and References
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment (APUE)](https://www.amazon.com/Advanced-Programming-UNIX-Environment-3rd/dp/0321637739) - Stevens & Rago
- [Linux Man Pages](https://man7.org/linux/man-pages/) - System calls reference
- [Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)
- [Shell Syntax](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) - POSIX specification

### Tutorials and Articles
- [Writing a Unix Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/) - Stephen Brennan
- [Building a Shell](https://github.com/tokenrove/build-your-own-shell) - Tutorial series
- [Process Management in Unix](https://www.geeksforgeeks.org/process-management-in-unix/)

### AI Usage
AI assistance (GitHub Copilot, ChatGPT) was used for the following tasks:
- **Code structure suggestions**: Initial architecture and organization patterns
- **Documentation**: Generating code comments and README structure
- **Research**: Understanding POSIX shell behavior and edge cases

No AI-generated code was used directly without understanding and adaptation. All core logic was written and validated manually.

## Testing

The project includes a test suite from [minishell_tester](https://github.com/LucasKuhn/minishell_tester):

```bash
cd minishell_tester
./tester
```

## Known Limitations

- No support for logical operators (`&&`, `||`)
- No wildcard expansion (`*`)
- Limited signal handling during command execution
- No job control or background processes

## Authors

- **lpons** - [GitHub Profile]
- **hammar** - [GitHub Profile]

## License

This project is part of the 42 School curriculum and follows the school's guidelines.
