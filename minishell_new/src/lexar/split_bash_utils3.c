/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:29:55 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:00:50 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	ft_pipe_special(char *input, char *delimeter, t_split *split)//3
{
	if (split->i == 0)
	{
		if (!ft_strchr(delimeter, input[split->i + 1]))
		{
			save_word(split, input, delimeter);
			split->result[split->a++] = ft_substr(input, split->i, 1);
			split->i++;
		}
	}
	else if (!ft_strchr(delimeter, input[split->i - 1])
		|| !ft_strchr(delimeter, input[split->i + 1]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	return (split->i);
}

int	ft_redir_special(char *input, char *delimeter, t_split *split)
{
	if (split->i == 0)
	{
		if (!ft_strchr(delimeter, input[split->i + 1]))
		{
			save_word(split, input, delimeter);
			split->result[split->a++] = ft_substr(input, split->i, 1);
			split->i++;
		}
	}
	else if ((!ft_strchr(delimeter, input[split->i - 1])
			|| !ft_strchr(delimeter, input[split->i + 1])))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 1);
		split->i++;
	}
	return (split->i);
}

int	ft_appdoc_special(char *input, char *delimeter, t_split *split)
{
	if (split->i == 0)
	{
		if (!ft_strchr(delimeter, input[split->i + 2]))
		{
			save_word(split, input, delimeter);
			split->result[split->a++] = ft_substr(input, split->i, 2);
			split->i = split->i + 2;
		}
	}
	else if (!ft_strchr(delimeter, input[split->i - 1])
		|| !ft_strchr(delimeter, input[split->i + 2]))
	{
		save_word(split, input, delimeter);
		split->result[split->a++] = ft_substr(input, split->i, 2);
		split->i = split->i + 2;
	}
	return (split->i);
}
