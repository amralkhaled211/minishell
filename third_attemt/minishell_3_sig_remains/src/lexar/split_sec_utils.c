/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:07:12 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 12:51:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	freeing(char **result, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(result[i]);
		i++;
	}
	free (result);
}

int	get_end_q(char *s, char *delimeter, t_split *split)
{
	int	len;
	int	tmp;

	tmp = split->i + 1;
	len = ft_strlen(s);
	while (tmp < len)
	{
		if (is_quote(s[tmp]))
			return (tmp);
		else if (!s[tmp] || ft_strchr(delimeter, s[tmp]))
			return (tmp - 1);
		tmp++;
	}
	return (tmp - 1);
}

int	get_start_q(char *s, char *delimeter, t_split *split)
{
	int	tmp;

	tmp = split->i;
	if (tmp == 0)
		return (tmp);
	while (tmp >= 0)
	{
		if (ft_strchr(delimeter, s[tmp]))
			return (tmp + 1);
		tmp--;
	}
	return (tmp + 1);
}

int	get_start(char *s, char *delimeter, t_split *split)
{
	int	tmp;

	tmp = split->i;
	while (tmp >= 0 && ft_strchr(delimeter, s[tmp]))
		tmp--;
	while (tmp >= 0)
	{
		if (ft_strchr(delimeter, s[tmp]))
			return (tmp + 1);
		tmp--;
	}
	return (tmp + 1);
}

int	get_end(char *s, char *delimeter, t_split *split)
{
	int	len;
	int	tmp;

	tmp = split->i;
	len = ft_strlen(s);
	while (tmp < len)
	{
		if (ft_strchr(delimeter, s[tmp]) || !s[tmp])
			return (tmp - 1);
		tmp++;
	}
	return (tmp - 1);
}
