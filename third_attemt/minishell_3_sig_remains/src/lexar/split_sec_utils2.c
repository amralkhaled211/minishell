/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:09:52 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 12:14:29 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	get_token_q(char *s, char *delimeter, t_split *split)
{
	int	len;

	split->word_end = get_end_q(s, delimeter, split);
	if (split->i != split->word_end && is_quote(s[split->word_end]))
	{
		split->in_quotes = !split->in_quotes;
		split->quote_char = s[split->word_end];
		return (split->word_end);
	}
	len = split->word_end - split->word_start + 1;
	split->result[split->a++] = ft_substr(s, split->word_start, len);
	if (!split->result[split->a - 1])
		return (freeing(split->result, split->a - 1), -1);
	split->word_end++;
	while (s[split->word_end] && ft_strchr(delimeter, s[split->word_end]))
		split->word_end++;
	return (split->word_end);
}

int	get_token_two(char *s, char *delimeter, t_split *split)
{
	int	len;

	split->word_start = get_start(s, delimeter, split);
	len = split->i - split->word_start;
	split->result[split->a] = ft_substr(s, split->word_start, len);
	if (!split->result[split->a])
		return (freeing(split->result, split->a - 1), -1);
	split->a++;
	return (split->i);
}
