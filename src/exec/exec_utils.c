

#include "../include/minishell.h"
#include "../libft/libft.h"

int do_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
    int cb;

    cb = check_builtin(cmds, shell, fd);
    if (cb == 0)
        return (0);
    close_pipes(cmds, fd);
    restore(shell);
    fd[2][0] += 1;
    if (cb == -1)
        fd[2][1] = 1;
    return (cb);
}

int     get_status(int last_pid)
{
    int status;

    waitpid((pid_t) last_pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        return (128 + WTERMSIG(status));
    return (status);
}

int is_dir(char *path)
{
    struct stat st;

    if (stat(path, &st) != 0) {
        perror("stat");
        return 0;
    }

    return S_ISDIR(st.st_mode);
}

int exit_exec(char **args, char *str)
{
    struct stat st;
    char *cmd;

    cmd = args[0];
    if (!cmd || cmd[0] == '\0')
        exit(0);
    if (strchr(cmd, '/')) 
    {
        if (stat(cmd, &st) != 0)
            (fprintf(stderr, "No such file or directory\n"),
            exit(127));
        if (S_ISDIR(st.st_mode))
            (fprintf(stderr, "Is a directory\n"),
            exit(126));
        if (access(cmd, X_OK) != 0)
            (fprintf(stderr, "Permission denied\n"),
            exit(126));
    }
    if (!str)
        (fprintf(stderr, "command not found\n"), exit(127));
    if (S_ISDIR(st.st_mode))
        (fprintf(stderr, "Is a directory\n"), exit(126));
    if (access(str, X_OK) != 0)
        (fprintf(stderr, "Permission denied\n"), exit(126));
    return (0);
}
