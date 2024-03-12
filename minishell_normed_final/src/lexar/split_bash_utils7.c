/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bash_utils7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:37:13 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:03:06 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pipe_special(int *count, char *delimeter, char *s, int i)
{
	if (!ft_strchr(delimeter, s[i - 1]) && !ft_strchr(delimeter, s[i + 1])
		&& (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))
		(*count) = (*count + 2);
	else
		(*count)++;
	i++;
	return (i);
}

int	redir_special(int *count, char *delimeter, char *s, int i)
{
	if (!ft_strchr(delimeter, s[i - 1]) && !ft_strchr(delimeter, s[i + 1])
		&& (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))
		(*count) = (*count + 2);
	else
		(*count)++;
	i++;
	return (i);
}

int	appdoc_special(int *count, char *delimeter, char *s, int i)
{
	if (!ft_strchr(delimeter, s[i - 1]) && !ft_strchr(delimeter, s[i + 2])
		&& (!is_quote(s[i - 1]) || !is_op_special(s, i, NULL)))
		(*count) = (*count + 2);
	else if (!ft_strchr(delimeter, s[i - 1]))
		(*count)++;
	else if (!ft_strchr(delimeter, s[i + 2]))
		(*count)++;
	i = i + 2;
	return (i);
}
