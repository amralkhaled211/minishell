/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:09:52 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:50:29 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	quote_cont(t_split *split, char *s)
{
	split->in_quotes = !split->in_quotes;
	split->quote_char = s[split->word_end];
	return (split->word_end);
}

int	get_token_q(t_token *token, char *s, char *delimeter, t_split *split)
{
	int		len;
	char	*tmp;

	split->word_end = get_end_q(token, s, delimeter, split);
	if (split->i != split->word_end && is_quote(s[split->word_end]))
		return (quote_cont(split, s));
	len = split->word_end - split->word_start + 1;
	split->result[split->a++] = ft_substr(s, split->word_start, len);
	if (!split->result[split->a - 1])
		return (freeing(split->result, split->a - 1), -1);
	tmp = handle_quotes(NULL, split->result[split->a -1], 1);
	if (!tmp)
		return (freeing(split->result, split->a - 1), -1);
	free(split->result[split->a -1]);
	split->result[split->a - 1] = tmp;
	if (joining_exp_end(token, split, split->word_start) == -1)
		return (freeing(split->result, split->a - 1), -1);
	split->word_end++;
	while (s[split->word_end] && ft_strchr(delimeter, s[split->word_end])
		&& !is_exp(token, split, split->word_end))
		split->word_end++;
	return (split->word_end);
}

int	get_token_two(t_token *token, char *s, char *delimeter, t_split *split)
{
	int		len;
	char	*tmp;

	split->word_start = get_start(token, s, delimeter, split);
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
	return (split->i);
}
