#include "../microshell.h"

static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free(tmp);
		}
	}
	free_str_array(tab);
	return (str);
}

char	*doc_expand(t_shell *shell, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(shell, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

char	*var_expander_heredoc(t_shell *shell, char *str)
{
	int	i;

	i = 0;

	while (str[i])
	{
		if (str[i] ==  '$'
			&&  is_spertor(str[i + 1]) ==  false
			&&  str[i + 1]  != '"'  &&  str[i + 1] != '\'')
			str = replace_str_heredoc(str,
					valid_var(str + i, shell), i);
		else
			i++;
	}
	return(str);
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = delete_and_replace_for_doc(str, var_value, index);
		free(tmp);
	}
	free(var_value);
	return (str);
}

