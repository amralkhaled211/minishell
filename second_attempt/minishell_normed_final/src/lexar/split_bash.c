/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:00:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 12:45:45 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

size_t	count_words(char *s, t_split *split)
{
	int	i;
	int	count;
	int	check_i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		check_i = i;
		i = count_helper(s, split, i, &count);
		if (check_i != i)
			continue ;
		if (check_i == i)
		{
			split->is_word = true;
			i++;
		}
	}
	if (split->is_word || split->in_quotes)
		count++;
	return (count);
}

int	count_helper(char *s, t_split *split, int i, int *count)
{
	int	check_i;

	check_i = i;
	i = count_quote_part(s, split, i, count);
	if (check_i != i)
		return (i);
	i = first_char_count(s, split, i, count);
	if (check_i != i)
		return (i);
	i = non_first_char_count(s, split, i, count);
	if (check_i != i)
		return (i);
	return (i);
}

static void	init_res(t_split *split)
{
	int	i;

	i = 0;
	while (i < split->num_words)
	{
		split->result[i] = NULL;
		i++;
	}
}

char	**ft_split_bash(char *input, char *delimeter)
{
	t_split	split;

	reset_split_var(&split);
	split.num_words = count_words(input, &split);
	if (!split.num_words)
		return (NULL);
	reset_split_var(&split);
	split.result = malloc(sizeof(char *) * (split.num_words + 1));
	if (!split.result)
		return (NULL);
	init_res(&split);
	if (handle_splitting(&split, input, delimeter) == -1)
		return (NULL);
	return (before_end_split(&split, input, delimeter));
}

int	handle_splitting(t_split *split, char *input, char *delimeter)
{
	int	check_i;

	while (input[split->i])
	{
		check_i = split->i;
		split->i = quote_handling(split, input, delimeter);
		if (split->i == -1)
			return (-1);
		else if (check_i != split->i)
			continue ;
		split->i = check_char(split, input, delimeter);
		if (split->i == -1)
			return (-1);
		if (split->i == check_i)
		{
			split->is_word = true;
			split->i++;
		}
	}
	return (1);
}
