/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:57:35 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/03 19:00:21 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static bool	is_spertor(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	return (false);
}

 static bool handel_quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\"')
			return (false);
		else if (str[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

void	expander(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while(token[i].type != TOKEN_END)
	{
		if(token[i].type == TOKEN_WORD)
		{
			j = 0;
			while (token[i].value[j])
			{
				if(token[i].value[j] == '$' && is_spertor(token[i].value[j + 1]) == false &&
					handel_quotes(token[i].value) == false )
				{
					change_var_to_val(token, valid_var(token[i].value + j, shell), j, i);
				}
				//else
				j++;
			}
		}
		i++;
	}
}
