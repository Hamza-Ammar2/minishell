#include "../include/minishell.h"
#include "../libft/libft.h"

static char	*tilde(char *str, t_shell *shell, int quote_type)
{
	t_env	*home_env;
	char	*home;
	char	*til;

	home_env = find_env(shell, "HOME");
	if (home_env)
		home = home_env->value;
	else
		home = "";
	if (*str == '~' && (str[1] == '\0' || str[1] == '/'))
		til = ft_strjoin(home, str + 1);
	else
		til = ft_strdup(str);
	if (!til)
		return (NULL);
	str = expand_word(shell, til, quote_type);
	return (free(til), str);
}

static char	**expand_words(char **words, t_shell *shell)
{
	int		j;
	char	*expanded;

	j = 0;
	while (words && words[j])
	{
		expanded = expand_str(shell, words[j], QUOTE_NONE);
		if (!expanded)
			return (free_splits(words), NULL);
		free(words[j]);
		words[j] = expanded;
		j++;
	}
	return (words);
}

char	**wraper(t_token **args, t_shell *shell)
{
	int		j;
	char	*expanded;
	char	**words;

	j = 0;
	words = NULL;
	while (args[j])
	{
		expanded = tilde(args[j]->value, shell, args[j]->quote_type);
		words = extract_words(words, expanded);
		free(expanded);
		if (!words)
			return (NULL);
		j++;
	}
	return (expand_words(words, shell));
}
