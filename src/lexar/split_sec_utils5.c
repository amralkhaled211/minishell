/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sec_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:01:57 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 21:02:33 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_3d_array(t_split *split, int j)
{
	int	i;
	int	k;

	i = -1;
	while (++i <= j)
	{
		if (!split->exp_res[i])
			continue ;
		k = -1;
		while (split->exp_res[i][++k])
			free(split->exp_res[i][k]);
		free(split->exp_res[i]);
	}
	free(split->exp_res);
}

int	joining_exp_end2(t_split *split)
{
	char	*tmp;

	tmp = ft_strjoin(split->result[split->a - 2],
			split->result[split->a - 1]);
	if (!tmp)
		return (-1);
	free(split->result[split->a - 2]);
	free(split->result[split->a - 1]);
	split->result[split->a - 2] = tmp;
	split->a--;
	return (0);
}

int	joining_exp_end(t_token *token, t_split *split, int start)
{
	int		sub;
	int		len;

	if (start > 0 && !is_exp(token, split, start - 1))
		return (0);
	sub = split->exp_i - 1;
	if (sub == -1)
		return (0);
	while (sub >= 0 && token->exp_pos[sub].unset)
		sub--;
	if (sub >= 0 && split->exp_res[sub])
		len = ft_strlen(token->array_exp[sub]) - 1;
	else
		return (0);
	if (!ft_strchr(" \t", token->array_exp[sub][len]))
		return (joining_exp_end2(split));
	return (0);
}
