/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 20:59:40 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 21:00:09 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_exp(t_token *token, t_split *split, int i)
{
	int		n;

	n = 0;
	(void)split;
	while (n <= token->j)
	{
		if (!token->exp_pos[n].unset && !token->exp_pos[n].in_quote)
			if ((i >= token->exp_pos[n].start && i <= token->exp_pos[n].end))
				return (true);
		n++;
	}
	return (false);
}

bool	space_in_prev_exp(t_split *split, t_token *token)
{
	int	len;
	int	tmp_exp_i;

	if (split->exp_i == 0)
		return (false);
	if (!is_exp(token, split, split->i - 1))
		return (false);
	tmp_exp_i = update_exp_i(token, split, split->i - 1);
	if (!token->array_exp[tmp_exp_i])
		return (false);
	len = ft_strlen(token->array_exp[tmp_exp_i]) - 1;
	if (ft_strchr(" \t", token->array_exp[tmp_exp_i][len]))
		return (true);
	return (false);
}

int	cpy_exp_res(t_split *split, int j, int len)
{
	errno = 0;
	while (++j <= len)
	{
		split->result[split->a++] = ft_strdup(split->exp_res[split->exp_i][j]);
		if (!split->result[split->a - 1] && errno != 0)
			return (-1);
	}
	return (0);
}

int	joining_exp_beg(t_token *token, t_split *split)
{
	int		j;
	char	*tmp;
	int		len;

	len = array_len(split->exp_res[split->exp_i]) - 1;
	j = 0;
	if (split->a != 0 && !ft_strchr(" \t", token->array_exp[split->exp_i][j])
			&& !space_in_prev_exp(split, token))
	{
		tmp = ft_strjoin(split->result[split->a - 1],
				split->exp_res[split->exp_i][j]);
		if (!tmp)
			return (-1);
		free(split->result[split->a - 1]);
		split->result[split->a - 1] = tmp;
	}
	else
	{
		split->result[split->a++] = ft_strdup(split->exp_res[split->exp_i][j]);
		if (!split->result[split->a - 1] && errno != 0)
			return (-1);
	}
	return (cpy_exp_res(split, j, len));
}
