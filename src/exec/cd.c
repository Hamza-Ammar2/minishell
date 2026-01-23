

#include "../include/minishell.h"
#include "../libft/libft.h"

static char *get_dir(char *arg, t_shell *shell)
{
    t_env *home_env;
    char   *home;

    home_env = find_env(shell, "HOME");
    if (!home_env /* && (!arg || (arg && arg[0] == '~')) */)
        home = "";
    else
        home = home_env->value;
    if (!arg || ft_strcmp(arg, "--") == 0)
        return (ft_strdup(home));
    else if (arg[0] == '~' && (arg[1] == '/' || arg[1] == '\0'))
        return (ft_strjoin(home, arg + 1));
    else if (ft_strcmp(arg, "-") == 0)
    {
        home_env = find_env(shell, "OLDPWD");
        if (!home_env)
            return (fprintf(stderr, "cd: OLDPWD not set\n"), NULL);
        home = home_env->value;
        write(STDOUT_FILENO, home, ft_strlen(home));
        write(STDOUT_FILENO, "\n", 1);
        return (ft_strdup(home));
    }
    return (ft_strdup(arg));
}

static int  update_pwd(t_shell *shell, char *pwd)
{
    t_env   *old;
    char    *oldpwd;

    old = find_env(shell, pwd);
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("cd: getcwd failed"), 1);
    if (!old)
    {
        old = malloc(sizeof(t_env));
        if (!old)
            return (perror("cd: malloc failed"), 1);
        old->key = ft_strdup(pwd);
        old->value = oldpwd;
        old->next = shell->env;
        shell->env = old;
    }
    else
    {
        free(old->value);
        old->value = oldpwd;
    }
    return (0);
}

int    cd(char **args, t_shell *shell)
{
    char    *dir;
    int     c;

    c = 0;
    while (args[c])
        c++;
    if (c > 1)
        return (fprintf(stderr, "cd: too many arguments\n"), 1);
    if (args[0] && !args[0][0])
        return (0);
    dir = get_dir(args[0], shell);
    if (!dir)
        return (1);
    if (update_pwd(shell, "OLDPWD") == 1)
        return (free(dir), 1);
    if (!is_dir(dir))
        return (free(dir), 1);
    if (chdir(dir) == -1)
        return (free(dir), perror("chdir failed\n"), 1);
    return (free(dir), update_pwd(shell, "PWD"), 0);
}
