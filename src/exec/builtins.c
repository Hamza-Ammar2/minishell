

#include "../include/minishell.h"
#include "../libft/libft.h"

void    pwd()
{
    char    *cwd;

    cwd = getcwd(NULL, 0);
    if (!cwd)
        perror("getcwd failed");
    printf("%s\n", cwd);
    free(cwd);
}

void    cd(char **args)
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
        perror("cd: too many arguments\n");
        return ;
    }
    if (chdir(dir) == -1)
        perror("chdir failed");
}

void    env(t_shell *shell)
{
    t_env   *current;
    char    **env;

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
}

void    echo(char **args)
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
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
}
