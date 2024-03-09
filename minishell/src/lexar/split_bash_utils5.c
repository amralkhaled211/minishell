/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:34:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 12:49:35 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	reset_split_var(t_split *split)//5
{
	split->a = 0;
	split->i = 0;
	split->arg_end = 0;
	split->arg_start = 0;
	split->in_quotes = false;
	split->is_word = false;
	split->q_start = 0;
	split->flag = 0;
	split->quote_char = '\0';
	split->result = NULL;
	split->word_start = 0;
	split->word_end = 0;
	split->processed = 0;
}

int	ft_get_redir(char *input, int i, t_split *split)
{
	(void)split;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
		{
			return (2);
		}
		else
			return (1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	return (0);
}

int	is_op_special(char *input, int i, t_split *split)
{
	if (input[i] == '|')
		return (1);
	else if (ft_get_redir(input, i, split) == 1)
		return (2);
	else if (ft_get_redir(input, i, split) == 2)
		return (3);
	return (0);
}

static bool	cond_init_start(t_split *split, char *input, char *deli, int c)
{
	if (c == 1 && !split->in_quotes && split->i > 0
		&& !ft_strchr(deli, input[split->i - 1]))
		return (true);
	if (c == 2 && !split->in_quotes && split->i > 0)
		return (true);
	return (false);
}

void	init_start_end(t_split *split, char *input, char *deli)
{
	if (cond_init_start(split, input, deli, 1)
		&& !is_op_special(input, split->i - 1, split) && !split->flag)
	{
		split->q_start = split->i;
		while (split->q_start > 0 && !ft_strchr(deli, input[split->q_start]))
		{
			if (is_op_special(input, split->q_start - 1, split))
				break ;
			split->q_start--;
		}
		if (split->q_start == 0 && !ft_strchr(deli, input[split->q_start]))
			split->arg_start = split->q_start;
		else
			split->arg_start = split->q_start + 1;
		split->q_start = split->i;
	}
	else if (cond_init_start(split, input, deli, 2)
		&& (ft_strchr(deli, input[split->i - 1])
			|| is_op_special(input, split->i - 1, split)) && !split->flag)
	{
		split->q_start = split->i;
		split->arg_start = split->i;
	}
}
