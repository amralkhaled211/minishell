/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:25 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 17:03:12 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	count_words_sec(char const *s, char *delimeter)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && ft_strchr(delimeter, s[i]))
			i++;
		if (s[i] != '\0')
			j++;
		while (!ft_strchr(delimeter, s[i]) && s[i] != '\0')
			i++;
	}
	return (j);
}

char	**ft_split_sec(char *s, char *deli)
{
	t_split	split;
	char	*tmp;

	reset_split_var(&split);
	if (!s)
		return (NULL);
	split.result = malloc(sizeof(char *) * (count_words_sec(s, deli) + 3));
	if (split.result == NULL)
		return (NULL);
	tmp = ft_strtrim(s, " \t");
	if (!tmp)
		return (free(split.result), NULL);
	s = tmp;
	if (!s[split.i])
	{
		split.result[0] = ft_strdup(s);
		split.result[1] = NULL;
		return (free(tmp), split.result);
	}
	if (mini_split_sec(s, deli, &split) == -1)
		return (free(tmp), NULL);
	if (split_last_part(s, deli, &split) == -1)
		return (free(tmp), NULL);
	split.result[split.a] = NULL;
	return (free(tmp), split.result);
}

int	split_last_part(char *s, char *delimeter, t_split *split)
{
	int	len;

	if (s[split->i] == 0 && !ft_strchr(delimeter, s[split->i - 1])
		&& split->in_quotes)
	{
		len = split->i - split->word_start + 1;
		split->result[split->a++] = ft_substr(s, split->word_start, len);
		if (!split->result[split->a - 1])
			return (freeing(split->result, split->a - 1), -1);
	}
	else if (s[split->i] == 0 && !ft_strchr(delimeter, s[split->i - 1])
		&& !split->in_quotes && !split->processed)
	{
		if (get_token_two(s, delimeter, split) == -1)
			return (-1);
	}
	return (0);
}

int	mini_split_sec(char *s, char *delimeter, t_split *split)
{
	while (s[split->i])
	{
		if ((s[split->i] == '"' || s[split->i] == '\'')
			&& (!split->in_quotes || split->quote_char == s[split->i]))
		{
			if (process_quote(s, delimeter, split) == -1)
				return (-1);
		}
		else if (split->in_quotes)
			split->i++;
		else if (!split->in_quotes && !ft_strchr(delimeter, s[split->i]))
		{
			split->i++;
			split->processed = 0;
		}
		else if (!split->in_quotes && (ft_strchr(delimeter, s[split->i])
				|| s[split->i + 1] == 0))
		{
			if (get_token_two(s, delimeter, split) == -1)
				return (-1);
			while (s[split->i] && ft_strchr(delimeter, s[split->i]))
				split->i++;
		}
	}
	return (0);
}

int	process_quote(char *s, char *delimeter, t_split *split)
{
	split->in_quotes = !split->in_quotes;
	if (split->in_quotes)
	{
		split->quote_char = s[split->i];
		split->word_start = get_start_q(s, delimeter, split);
	}
	if (!split->in_quotes)
	{
		split->i = get_token_q(s, delimeter, split);
		if (split->i == -1)
			return (-1);
		split->processed = 1;
	}
	else if (s[split->i])
		split->i++;
	return (0);
}
