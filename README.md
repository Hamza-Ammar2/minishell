# Minishell - Minimal Core

A very simple shell that demonstrates basic readline functionality.

## What it does:
- Shows a prompt: `minishell$ `
- Reads user input using readline
- Saves input to history (use up/down arrows)
- Echoes back what you typed
- Exits on Ctrl+D

## Build:
```bash
make
```

## Run:
```bash
./minishell
```

## Test:
```bash
./minishell
minishell$ hello world
You typed: hello world
minishell$ test 123
You typed: test 123
minishell$ [Press Ctrl+D to exit]
exit
```

## Current Structure:
```
include/minishell.h  - Simple shell struct with exit_status
src/main.c          - Main loop with readline
src/init.c          - Initialize shell
src/cleanup.c       - Cleanup history
```

## Next Steps:
Now you can incrementally add features:
1. Parse simple commands (split by spaces)
2. Execute external commands (fork + execve)
3. Add built-ins (echo, pwd, cd, etc.)
4. Add pipes
5. Add redirections
6. And so on...

Each feature can be added one at a time and tested!
