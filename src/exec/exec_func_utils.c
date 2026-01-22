

#include "../include/minishell.h"
#include "../libft/libft.h"

static int  pce(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "pwd") == 0 ||
     ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "export") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds, fd))
        return (-1);
    if (ft_strcmp(args[0], "pwd") == 0)
        fd[2][1] = pwd(&args[1]);
    else if (ft_strcmp(args[0], "cd") == 0)
        fd[2][1] = cd(&args[1]);
    else
        fd[2][1] = export(&args[1], shell);
    return (1);
}

static int  eeu(t_command *cmds, t_shell *shell, int fd[3][2], char **args)
{
    if (!(ft_strcmp(args[0], "env") == 0 ||
     ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "unset") == 0))
        return (0);
    if (connect_pipes(cmds, fd) == -1)
        return (-1);
    if (!direct_io(shell, cmds, fd))
        return (-1);
    if (ft_strcmp(args[0], "env") == 0)
        fd[2][1] = env(&args[1], shell);
    else if (ft_strcmp(args[0], "echo") == 0)
        fd[2][1] = echo(&args[1]);
    else
        fd[2][1] = unset(shell, &args[1]);
    return (1);
}

int     check_builtin(t_command *cmds, t_shell *shell, int fd[3][2])
{
    char **args;
    int i;

    args = wraper(cmds->args, shell);
    // FIX: If all tokens expanded to empty strings, args[0] will be NULL
    // In this case, there's no command to execute, just return success
    if (!args || !args[0])
        return (free_splits(args), 0);
    i = pce(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (free_splits(args), i);
    i = eeu(cmds, shell, fd, args);
    if (i == -1 || i == 1)
        return (free_splits(args), i);
    free_splits(args);
    return (0);
}

void    free_splits(char **splits)
{
    int i;

    if (!splits)
        return ;
    i = 0;
    while (splits[i])
        free(splits[i++]);
    free(splits);
}

// #PF Tilde expansion function - expands ~ to HOME at start of string
// Only expands if:  1. String starts with '~'
//                   2. Not in single quotes (QUOTE_SINGLE)
//                   3. Followed by '/' or end of string
static char *expand_tilde(t_shell *shell, char *str, int quote_type)
{
    t_env   *home_env;
    char    *expanded;

    // #PF Don't expand in single quotes or if doesn't start with ~
    if (!str || quote_type == QUOTE_SINGLE || str[0] != '~')
        return (ft_strdup(str));
    // #PF Only expand ~ or ~/path, not ~user
    if (str[1] != '\0' && str[1] != '/')
        return (ft_strdup(str));
    // #PF Get HOME environment variable
    home_env = find_env(shell, "HOME");
    if (!home_env || !home_env->value)
        return (ft_strdup(str)); // #PF If no HOME, keep tilde as-is
    // #PF Join HOME with rest of path (skip the ~)
    expanded = ft_strjoin(home_env->value, str + 1);
    if (!expanded)
        return (perror("expand_tilde: malloc failed"), NULL);
    return (expanded);
}

char **wraper(t_token **args, t_shell *shell)
{
    int     count;
    int     j;
    char    **args_array;
    char    *expanded;

    count = 0;
    while (args[count])
        count++;
    args_array = malloc(sizeof(char *) * (count + 1));
    if (!args_array)
        return (perror("could not create arguments list"), NULL);
    int i = 0;
    j = 0;
    // FIX: Skip empty expanded tokens (e.g., undefined variables) to match bash behavior
    while (i < count)
    {
        // #PF Apply tilde expansion first, before variable expansion
        expanded = expand_tilde(shell, args[i]->value, args[i]->quote_type);
        if (!expanded)
            return (perror("could not create arguments list"), free_splits(args_array), NULL);
        // #PF Then apply variable expansion on the tilde-expanded string
        char *final = expand_str(shell, expanded, args[i]->quote_type);
        free(expanded); // #PF Free intermediate tilde-expanded string
        if (!final)
            return (perror("could not create arguments list"), free_splits(args_array), NULL);
        // FIX: Only add non-empty strings to args_array (bash removes empty unquoted expansions)
        if (final[0] != '\0')
        {
            args_array[j] = final;
            j++;
        }
        else
            free(final); // FIX: Free empty string since we're not adding it to array
        i++;
    }
    args_array[j] = NULL;
    return (args_array);
}
