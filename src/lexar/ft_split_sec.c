/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_sec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:25 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 21:02:29 by aismaili         ###   ########.fr       */
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

void	null_exp_res(t_split *split, int j)
{
	int	i;

	i = -1;
	while (++i < j)
		split->exp_res[i] = NULL;
}

int	only_spaces_case(t_token *token, t_split *split, char *s)
{
	char	*tmp;

	errno = 0;
	tmp = ft_strtrim(s, " \t");
	if (!tmp && errno != 0)
		return (-1);
	if (!tmp[split->i])
	{
		split->result[0] = ft_strdup(tmp);
		if (!split->result[0])
			return (free(tmp), -1);
		split->result[1] = NULL;
		token->a = 1;
		return (free(tmp), 1);
	}
	free(tmp);
	return (0);
}

char	**ft_split_sec(t_token *token, char *s, char *deli)
{
	t_split	split;
	int		tmp;

	reset_split_var(&split);
	if (!s)
		return (NULL);
	split.result = malloc(sizeof(char *) * (count_words_sec(s, deli) + 3));
	if (split.result == NULL)
		return (NULL);
	tmp = only_spaces_case(token, &split, s);
	if (tmp == -1)
		return (free(split.result), NULL);
	else if (tmp == 1)
		return (split.result);
	split.exp_res = malloc(sizeof(char **) * (token->j + 1));
	if (!split.exp_res)
		return (free(split.result), NULL);
	null_exp_res(&split, token->j + 1);
	if (mini_split_sec(token, s, deli, &split) == -1)
		return (free_3d_array(&split, token->j), NULL);
	if (split_last_part(token, s, deli, &split) == -1)
		return (free_3d_array(&split, token->j), NULL);
	split.result[split.a] = NULL;
	token->a = split.a;
	return (free_3d_array(&split, token->j), split.result);
}

int	split_last_part(t_token *token, char *s, char *delimeter, t_split *split)
{
	int		len;
	char	*tmp;

	if (s[split->i] == 0 && !ft_strchr(delimeter, s[split->i - 1])
		&& split->in_quotes)
	{
		len = split->i - split->word_start + 1;
		split->result[split->a++] = ft_substr(s, split->word_start, len);
		if (!split->result[split->a - 1])
			return (freeing(split->result, split->a - 1), -1);
		tmp = handle_quotes(NULL, split->result[split->a -1], 1);
		if (!tmp)
			return (freeing(split->result, split->a - 1), -1);
		free(split->result[split->a -1]);
		split->result[split->a -1] = tmp;
		if (joining_exp_end(token, split, split->word_start) == -1)
			return (freeing(split->result, split->a - 1), -1);
	}
	else if (s[split->i] == 0 && !ft_strchr(delimeter, s[split->i - 1])
		&& !split->in_quotes && !split->processed)
	{
		if (get_token_two(token, s, delimeter, split) == -1)
			return (-1);
	}
	return (0);
}
