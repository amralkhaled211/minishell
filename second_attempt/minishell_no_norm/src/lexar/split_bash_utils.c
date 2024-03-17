/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:25:54 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:00:07 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static bool	check_i_d_q1(t_split *split, char *input, char *delimeter, int c)
{
	if (c == 1)
	{
		if (split->i == 0 && !ft_strchr(delimeter, input[split->i + 1])
			&& !split->in_quotes)
			return (true);
	}
	if (c == 2)
	{
		if (split->i == 0 && !ft_strchr(delimeter, input[split->i + 2])
			&& !split->in_quotes)
			return (true);
	}
	return (false);
}

static bool	check_i_d_q2(t_split *split, char *input, char *deli, int c)
{
	if (c == 1)
	{
		if (split->i > 0 && (!ft_strchr(deli, input[split->i - 1])
				|| !ft_strchr(deli, input[split->i + 1])) && !split->in_quotes)
			return (true);
	}
	if (c == 2)
	{
		if (split->i > 0 && (!ft_strchr(deli, input[split->i - 1])
				|| !ft_strchr(deli, input[split->i + 2])) && !split->in_quotes)
			return (true);
	}
	return (false);
}

static bool	check_i_d_q3(t_split *split, char *input, char *delimeter)
{
	if (split->i > 0 && (ft_get_redir(input, split->i, split) == 1)
		&& (!ft_strchr(delimeter, input[split->i - 1])
			|| !ft_strchr(delimeter, input[split->i + 1])))
	{
		if ((!ft_strchr("<>", input[split->i + 1])
				&& !ft_strchr("<>", input[split->i - 1])) && !split->in_quotes)
			return (true);
	}
	return (false);
}

int	check_char(t_split *split, char *input, char *delimeter)
{
	if (input[split->i] == '|' && check_i_d_q1(split, input, delimeter, 1))
		split->i = ft_pipe_special(input, delimeter, split);
	else if ((ft_get_redir(input, split->i, split) == 1)
		&& check_i_d_q1(split, input, delimeter, 1))
		split->i = ft_redir_special(input, delimeter, split);
	else if ((ft_get_redir(input, split->i, split) == 2)
		&& check_i_d_q1(split, input, delimeter, 2))
		split->i = ft_appdoc_special(input, delimeter, split);
	else if (input[split->i] == '|'
		&& check_i_d_q2(split, input, delimeter, 1))
		split->i = ft_pipe_special(input, delimeter, split);
	else if ((ft_get_redir(input, split->i, split) == 2)
		&& check_i_d_q2(split, input, delimeter, 2))
		split->i = ft_appdoc_special(input, delimeter, split);
	else if (check_i_d_q3(split, input, delimeter))
		split->i = ft_redir_special(input, delimeter, split);
	else if ((ft_strchr(delimeter, input[split->i]) || input[split->i] == 0)
		&& !split->in_quotes)
	{
		if (save_word(split, input, delimeter))
			return (-1);
		split->i++;
	}
	return (split->i);
}
