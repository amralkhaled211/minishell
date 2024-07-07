/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:07:12 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:49:33 by aismaili         ###   ########.fr       */
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

int	get_end_q(t_token *token, char *s, char *delimeter, t_split *split)
{
	int	len;
	int	tmp;

	tmp = split->i + 1;
	len = ft_strlen(s);
	while (tmp < len)
	{
		if (is_exp(token, split, tmp))
			break ;
		if (is_quote(s[tmp]))
			return (tmp);
		else if (!s[tmp] || ft_strchr(delimeter, s[tmp]))
			return (tmp - 1);
		tmp++;
	}
	return (tmp - 1);
}

int	get_start_q(t_token *token, char *s, char *delimeter, t_split *split)
{
	int	tmp;

	tmp = split->i;
	if (tmp == 0)
		return (tmp);
	while (tmp >= 0)
	{
		if (is_exp(token, split, tmp))
			return (tmp + 1);
		if (ft_strchr(delimeter, s[tmp]))
			return (tmp + 1);
		tmp--;
	}
	return (tmp + 1);
}

int	get_start(t_token *token, char *s, char *delimeter, t_split *split)
{
	int	tmp;

	tmp = split->i;
	while (tmp >= 0 && ft_strchr(delimeter, s[tmp])
		&& !is_exp(token, split, tmp))
		tmp--;
	while (tmp >= 0)
	{
		if (is_exp(token, split, tmp))
			return (tmp + 1);
		if (ft_strchr(delimeter, s[tmp]))
			return (tmp + 1);
		tmp--;
	}
	return (tmp + 1);
}

int	get_end(t_token *token, char *s, char *delimeter, t_split *split)
{
	int	len;
	int	exp_pos_start;
	int	tmp;
	int	tmp2;

	tmp = split->i;
	len = ft_strlen(s);
	tmp2 = split->exp_i;
	while (tmp2 <= token->j && token->exp_pos[tmp2].unset)
		tmp2++;
	if (token->array_exp[tmp2])
		exp_pos_start = token->exp_pos[tmp2].start;
	else
		exp_pos_start = len;
	while (tmp < len && tmp > exp_pos_start)
	{
		if (ft_strchr(delimeter, s[tmp]) || !s[tmp])
			return (tmp - 1);
		tmp++;
	}
	return (tmp - 1);
}
