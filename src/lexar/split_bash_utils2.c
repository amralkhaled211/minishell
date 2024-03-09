/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:27:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 12:48:46 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static bool	quote_handle_cond1(t_split *split, char *input)//5
{
	if ((input[split->i] == '"' || input[split->i] == '\''
			|| split->flag == 2))
		return (true);
	return (false);
}

static bool	quote_handle_cond2(t_split *split, char *input)
{
	if (!split->in_quotes || split->quote_char == input[split->i]
		|| split->flag)
		return (true);
	return (false);
}

int	quote_handling(t_split *split, char *input, char *delimeter)
{
	if (quote_handle_cond1(split, input) && quote_handle_cond2(split, input))
	{
		init_start_end(split, input, delimeter);
		if (split->flag != 2)
		{
			if (split->flag == 1)
				split->flag = 0;
			split->in_quotes = !split->in_quotes;
			if (split->in_quotes)
				split->quote_char = input[split->i];
			else
				split->quote_char = '\0';
		}
		if (save_quote(split, input, delimeter))
			return (-1);
		split->i++;
	}
	return (split->i);
}

static bool	before_end_cond(t_split *split, char *input, char *delimeter)
{
	if (input[split->i] == 0 && !ft_strchr(delimeter, input[split->i - 1])
		&& !split->in_quotes)
		return (true);
	return (false);
}

char	**before_end_split(t_split *split, char *input, char *delimeter)
{
	int	len;

	if (split->in_quotes)
	{
		len = split->arg_end - split->arg_start + 1;
		split->result[split->a++] = ft_substr(input, split->arg_start, len);
		if (!split->result[split->a - 1])
			return (free_split_fail(split, split->a - 1), NULL);
	}
	else if (before_end_cond(split, input, delimeter))
	{
		if (save_word(split, input, delimeter))
			return (NULL);
	}
	split->result[split->a] = NULL;
	return (split->result);
}
