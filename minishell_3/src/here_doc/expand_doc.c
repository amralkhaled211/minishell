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

char	*add_spaces(int spaces, char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + spaces + 1));
	if (!new)
		return (free(str), NULL);
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

int	count_first_spaces(char	*line)
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

int	count_spaces(char *line)
{
	static int	j;
	int			spaces;

	spaces = 0;
	if (j == 0)
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
	if (line[j] == '\0')
		j = 0;
	return (spaces);
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
	while (str && str[i])
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
