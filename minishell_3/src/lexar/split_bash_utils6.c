/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:35:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:49:26 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '"')
		return (2);
	return (0);
}

int	save_quote(t_split *split, char *input, char *delimeter)
{
	int	len;

	if (!split->in_quotes && (ft_strchr(delimeter, input[split->i + 1])
			|| is_op_special(input, split->i + 1, split) || !input[split->i]))
	{
		split->arg_end = split->i;
		len = split->arg_end - split->arg_start + 1;
		split->result[split->a++] = ft_substr(input, split->arg_start, len);
		if (!split->result[split->a - 1])
		{
			free_split_fail(split, split->a - 1);
			return (1);
		}
		split->is_word = false;
		split->flag = 0;
	}
	else if (!split->in_quotes && is_quote(input[split->i + 1]))
		split->flag = 1;
	else if (!split->in_quotes && (!ft_strchr(delimeter, input[split->i + 1])
			|| !is_op_special(input, split->i + 1, split)))
		split->flag = 2;
	return (0);
}

int	ft_get_redir_edge(char *input, int i, t_split *split)
{
	(void)split;
	if (input[i] == '<')
	{
		if (i > 0 && input[i - 1] == '<')
			return (2);
		else
			return (1);
	}
	else if (input[i] == '>')
	{
		if (i > 0 && input[i - 1] == '>')
			return (2);
		else
			return (1);
	}
	return (0);
}

static bool	cond_save_word(t_split *split, char *input, char *deli)
{
	if ((split->word_end > 0 && !ft_strchr(deli, input[split->word_end - 1]))
		|| !ft_strchr(deli, input[split->word_end + 1]))
		return (true);
	return (false);
}

int	save_word(t_split *split, char *input, char *delimeter)
{
	int	len;

	if (split->is_word)
	{
		split->word_end = split->i - 1;
		while (split->word_end >= 0
			&& (!ft_strchr(delimeter, input[split->word_end])))
		{
			if (is_op_special(input, split->word_end, split)
				&& cond_save_word(split, input, delimeter))
				break ;
			split->word_end--;
		}
		if (ft_get_redir_edge(input, split->i - 1, split) == 2)
			split->word_start = split->word_end - 1;
		else
			split->word_start = split->word_end + 1;
		split->word_end = split->i;
		len = split->word_end - split->word_start;
		split->result[split->a++] = ft_substr(input, split->word_start, len);
		if (!split->result[split->a - 1])
			return (free_split_fail(split, split->a - 1), 1);
		split->is_word = false;
	}
	return (0);
}
