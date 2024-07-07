/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:57:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 20:57:57 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	update_exp_i(t_token *token, t_split *split, int i)
{
	int	n;

	(void)split;
	n = 0;
	while (n <= token->j)
	{
		if (!token->exp_pos[n].unset && !token->exp_pos[n].in_quote)
			if ((i >= token->exp_pos[n].start && i <= token->exp_pos[n].end))
				return (n);
		n++;
	}
	return (n);
}

int	handle_prim(t_token *token, char *s, char *delimeter, t_split *split)
{
	if ((s[split->i] == '"' || s[split->i] == '\'')
		&& (!split->in_quotes || split->quote_char == s[split->i])
		&& !is_exp(token, split, split->i))
	{
		if (process_quote(token, s, delimeter, split) == -1)
			return (-1);
		return (1);
	}
	else if (is_exp(token, split, split->i) && !split->in_quotes)
	{
		split->exp_i = update_exp_i(token, split, split->i);
		split->exp_res[split->exp_i] = ft_split(token->array_exp[split->exp_i],
				' ');
		if (!split->exp_res[split->exp_i] && errno != 0)
			return (freeing(split->result, split->a - 1), -1);
		if (joining_exp_beg(token, split) == -1)
			return (freeing(split->result, split->a - 1), -1);
		split->i = token->exp_pos[split->exp_i].end + 1;
		split->exp_i++;
		return (1);
	}
	return (0);
}

int	handle_nqword(t_token *token, t_split *split, char *s, char *deli)
{
	if (!split->in_quotes && (ft_strchr(deli, s[split->i])
			|| s[split->i + 1] == 0 || is_exp(token, split, split->i + 1)))
	{
		if (get_token_two(token, s, deli, split) == -1)
			return (-1);
		split->processed = 1;
		split->i++;
		while (s[split->i] && ft_strchr(deli, s[split->i])
			&& !is_exp(token, split, split->i))
			split->i++;
		return (1);
	}
	return (0);
}

int	mini_split_sec(t_token *token, char *s, char *delimeter, t_split *split)
{
	int	found;

	while (s[split->i])
	{
		found = handle_prim(token, s, delimeter, split);
		if (found == -1)
			return (-1);
		if (found != 0)
			continue ;
		else if (split->in_quotes)
			split->i++;
		else if (!split->in_quotes && !ft_strchr(delimeter, s[split->i])
			&& !is_exp(token, split, split->i + 1))
		{
			split->i++;
			split->processed = 0;
		}
		else
			if (handle_nqword(token, split, s, delimeter) == -1)
				return (-1);
	}
	return (0);
}

int	process_quote(t_token *token, char *s, char *delimeter, t_split *split)
{
	split->in_quotes = !split->in_quotes;
	if (split->in_quotes)
	{
		split->quote_char = s[split->i];
		split->word_start = get_start_q(token, s, delimeter, split);
	}
	if (!split->in_quotes)
	{
		split->i = get_token_q(token, s, delimeter, split);
		if (split->i == -1)
			return (-1);
		split->processed = 1;
	}
	else if (s[split->i])
		split->i++;
	return (0);
}
