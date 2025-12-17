

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
