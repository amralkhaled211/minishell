#include "../microshell.h"

static char	*ft_strjoin_doc(char *s1, char *s2, int spaces)///changed
{
	char				*new_str;
	unsigned int		i;
	unsigned int		j;

	i = 0;
	j = -1;
	if (s1 == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + spaces + 1));
	if (new_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[++j] != '\0')
		new_str[i + j] = s2[j];
	while(spaces-- > 0)
		new_str[i + j++] = ' ';
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

static	char	*add_spaces(int spaces, char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + spaces + 1));
	while (spaces > 0)
	{
		new[i] = ' ';
		i++;
		spaces--;
	}
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(str);
	return(new);
}

static	int	count_first_spaces(char	*line)
{
	int	spaces;
	int	j;

	j = 0;
	spaces = 0;
	while (line[j] == ' ')
	{
		j++;
		spaces++;
	}	
	return(spaces);
}

static int	count_spaces(char *line)
{
	static int	j;
	int		spaces;

	j = 0;
	spaces = 0;
	while (line[j] == ' ')
		j++;
	while (line[j])
	{
		if (line[j] == ' ')
		{
			while (line[j] == ' ')
			{
				spaces++;
				j++;
			}
				break;
		}
		else
			j++;
	}
	return (spaces);
}

static char	*make_str_from_tab(char **tab, char *line)
{
	char	*str;
	char	*tmp;
	int		i;
	int		spac;
	int		spac2;

	i = -1;
	while (tab[++i])
	{
		spac2 = count_first_spaces(line);
		spac = count_spaces(line);
		tmp = str;
		if (i == 0)
		{
			str = ft_strdup(tab[0]);
			if (!str)
				return(free(line), free_str_array(tab), NULL);
		}
		else
		{
			str = ft_strjoin_doc(tmp, tab[i], 0);
			if (!str)
				return (free(line), free_str_array(tab), free(tmp), NULL);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin_doc(tmp, " ", spac);
			if (!str)
				return(free(line), free_str_array(tab), free(tmp), NULL);
		}
	}
	tmp = str;
	if (spac2 != 0)
	{
		str = add_spaces(spac2, tmp);
		if (!str)
			return (free(line), free_str_array(tab), free(tmp), NULL);
	}
	return (free(line), free_str_array(tab), str);
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
				return (free(line), NULL);
		}
		i++;
	}
	return (make_str_from_tab(words, line));
}

char	*var_expander_heredoc(t_shell *shell, char	*str)
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
		str = delete_and_replace_for_doc(tmp, var_value, index);
		free(tmp);
	}
	free(var_value);
	return (str);
}
