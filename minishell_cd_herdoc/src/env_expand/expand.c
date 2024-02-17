/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:57:35 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/11 18:22:10 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_spertor(char c)
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
	while(token[i].type != TOKEN_END && token[i].type != TOKEN_DEFAULT)//segfault with out the second condition, why here? and not at the if statement?
	{
		if(token[i].type == TOKEN_WORD)
		{
			j = 0;
			if (i > 0 && token[i].value[j] == '$' && is_redir(token[i - 1]) && !is_var_val(token[i].value + 1, shell))
				token[i].amb_redir = true;
			while (token[i].type != TOKEN_END && token[i].value[j] && token[i].amb_redir == false)
			{
				if(token[i].value[j] == '$' && is_spertor(token[i].value[j + 1]) == false &&
					handel_quotes(token[i].value) == false && token[i].value[j + 1] != '"')
				{
					change_var_to_val(token, valid_var(token[i].value + j, shell), j, i);
				}
				j++;
			}
		}
		i++;
	}
}

/*
PROTECTION
STAGE 2
already setup
challange: destinguish between NULL for malloc fail and NULL for no Value
*/