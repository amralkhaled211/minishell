/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   expand_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:58:39 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/06 14:36:56 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	*ft_strjoin_doc(char *s1, char *s2, int spaces)
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
	while (spaces-- > 0)
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
	return (new);
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
	return (spaces);
}

static int	count_spaces(char *line)
{
	static int	j;
	int			spaces;

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
			break ;
		}
		else
			j++;
	}
	return (spaces);
}

static char	*create_initial_str(char **tab, char *line)
{
	char	*str;

	str = ft_strdup(tab[0]);
	if (!str)
		return (free(line), free_str_array(tab), NULL);
	return (str);
}

static char	*concatenate_strings(char *base, char *append, int spaces)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin_doc(base, append, 0);
	if (!result)
		return (free(base), free(append), NULL);
	if (append)
	{
		tmp = result;
		result = ft_strjoin_doc(tmp, " ", spaces);
		free(tmp);
		if (!result)
			return (free(base), free(append), NULL);
	}
	return (result);
}

static char	*add_initial_spaces(int spaces, char *base)
{
	char	*result;

	result = add_spaces(spaces, base);
	if (!result)
		free(base);
	return (result);
}

static char	*make_str_from_tab(char **tab, char *line)
{
	char	*str;
	int		i;
	int		spac;
	int		spac2;

	i = -1;
	while (tab[++i])
	{
		spac2 = count_first_spaces(line);
		spac = count_spaces(line);
		if (i == 0)
			str = create_initial_str(tab, line);
		else
			str = concatenate_strings(str, tab[i], spac);
		if (!str)
			return (free(line), free_str_array(tab), NULL);
	}
	if (spac2 != 0)
		str = add_initial_spaces(spac2, str);
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
		if (str[i] == '$'
			&& is_spertor(str[i + 1]) == false
			&& str[i + 1] != '"' && str[i + 1] != '\'')
		{
			str = replace_str_heredoc(str,
					valid_var(str + i, shell), i);
			if (!str && errno != 0)
				return (NULL);
			i = -1;
		}
		i++;
	}
	return (str);
}

static char	*delete_var_for_doc(char *var, int ind)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(var) - var_len(var + ind)) + 1);
	if (!new)
		return (NULL);
	while (var[i])
	{
		if (var[i] == '$' && i == ind)
		{
			i = i + var_len(var + ind) + 1;
			if (var[i] == '\0')
				break ;
		}
		new[j++] = var[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	errno = 0;
	tmp = NULL;
	if (var_value == NULL)
	{
		tmp = str;
		str = delete_var_for_doc(tmp, index);
		if (!str)
			return (free(tmp), free(var_value), NULL);
		free(tmp);
	}
	else
	{
		tmp = str;
		str = delete_and_replace_for_doc(tmp, var_value, index);
		if (!str)
			return (free(tmp), free(var_value), NULL);
		free(tmp);
	}
	free(var_value);
	return (str);
}
