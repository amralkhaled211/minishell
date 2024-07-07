/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_split_exp2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:40:14 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:40:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	default_exp_pos(t_token *token)
{
	int	i;

	i = 0;
	while (i <= token->j)
	{
		token->exp_pos[i].start = 0;
		token->exp_pos[i].end = 0;
		token->exp_pos[i].unset = false;
		token->exp_pos[i].in_quote = false;
		i++;
	}
}

bool	exp_in_quote(char *str, int a)
{
	int		i;
	bool	in_quote;

	i = -1;
	in_quote = false;
	while (str[++i])
	{
		if (str[i] == '"' && !in_quote)
			in_quote = true;
		else if (str[i] == '"' && in_quote)
			in_quote = false;
		if (str[i] == '$' && i == a)
			return (in_quote);
	}
	return (false);
}
