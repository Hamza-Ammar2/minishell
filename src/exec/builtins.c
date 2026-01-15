

#include "../include/minishell.h"
#include "../libft/libft.h"

int    pwd(char **args)
{
    char    *cwd;

    if (args && args[0])
    {
        fprintf(stderr, "pwd: too many arguments\n");
        return (1);
    }
    cwd = getcwd(NULL, 0);
    if (!cwd)
        return (perror("getcwd failed\n"), 1);
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}

int    cd(char **args)
{
    char    *dir;
    int     c;

    dir = args[0];
    if (!dir)
        dir = getenv("HOME");
    c = 0;
    while (args[c])
        c++;
    if (c > 1)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return (1);
    }
    if (!is_dir(dir))
        return (1);
    if (chdir(dir) == -1)
        return (perror("chdir failed\n"), 1);
    return (0);
}

int    env(char **args, t_shell *shell)
{
    t_env   *current;
    char    **env;

    if (args && args[0])
    {
        fprintf(stderr, "env: too many arguments\n");
        return (1);
    }
    current = shell->env;
    env = shell->envp;
    while (env && *env)
    {
        printf("%s\n", *env);
        env++;
    }
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (0);
}

int    echo(char **args)
{
    int     newline;
    int     i;

    newline = 1;
    i = 0;
    while (args[i] && ft_strcmp(args[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
        if (args[i + 1] && *args[i])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    return (0);
}
