/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:31:22 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:04:53 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	count_quote_part(char *s, t_split *split, int i, int *count)//5
{
	char	*delimeter;

	delimeter = " \t";
	if ((s[i] == '"' || s[i] == '\'')
		&& (!split->in_quotes || split->quote_char == s[i]))
	{
		if (i > 0 && !split->in_quotes && ft_strchr(delimeter, s[i - 1]))
			split->q_start = i;
		split->in_quotes = !split->in_quotes;
		if (split->in_quotes)
			split->quote_char = s[i];
		else
			split->quote_char = '\0';
		if (!split->in_quotes && (ft_strchr(delimeter, s[i + 1])
				|| is_op_special(s, i + 1, split)))
		{
			(*count)++;
			split->is_word = false;
		}
		i++;
	}
	return (i);
}

static bool	count_i_d_q1(t_split *split, char *input, char *delimeter, int i)
{
	if (i > 0 && (!ft_strchr(delimeter, input[i - 1])
			|| !ft_strchr(delimeter, input[i + 1])) && !split->in_quotes)
		return (true);
	return (false);
}

static bool	count_i_d_q2(t_split *split, char *input, char *delimeter, int i)
{
	if (i > 0 && (!ft_strchr(delimeter, input[i - 1])
			|| !ft_strchr(delimeter, input[i + 2])) && !split->in_quotes)
		return (true);
	return (false);
}

int	non_first_char_count(char *s, t_split *split, int i, int *count)
{
	char	*delimeter;

	delimeter = " \t";
	if (s[i] == '|' && count_i_d_q1(split, s, delimeter, i))
		i = pipe_special(count, delimeter, s, i);
	else if (ft_get_redir(s, i, split) == 1
		&& count_i_d_q1(split, s, delimeter, i))
		i = redir_special(count, delimeter, s, i);
	else if (ft_get_redir(s, i, split) == 2
		&& count_i_d_q2(split, s, delimeter, i))
		i = appdoc_special(count, delimeter, s, i);
	else if (i > 0 && (ft_strchr(delimeter, s[i])) && !split->in_quotes)
	{
		if (split->is_word)
		{
			(*count)++;
			split->is_word = false;
		}
		i++;
	}
	return (i);
}

int	first_char_count(char *s, t_split *split, int i, int *count)
{
	if (i == 0 && (s[i] == '|' || ft_get_redir(s, i, split)))
	{
		(*count)++;
		i++;
		if (ft_get_redir(s, i, split) == 2)
			i++;
	}
	return (i);
}
