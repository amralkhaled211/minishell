/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:57:35 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/07 14:49:38 by aismaili         ###   ########.fr       */
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
	while(token[i].type != TOKEN_END && token[i].type != TOKEN_DEFAULT)//segfault with out the second condition, why here? and not at the if statement?
	{
		if(token[i].type == TOKEN_WORD)
		{
			j = 0;
			//printf("after first if: token[%i].value[%i]: %c\n", i, j, token[i].value[j]);
			if (i > 0 && token[i].value[j] == '$' && is_redir(token[i - 1]) && !is_var_val(token[i].value + 1, shell))
				token[i].amb_redir = true;
			while (token[i].type != TOKEN_END && token[i].value[j] && token[i].amb_redir == false)
			{
				if(token[i].value[j] == '$' && is_spertor(token[i].value[j + 1]) == false &&
					handel_quotes(token[i].value) == false && token[i].value[j + 1] != '"')
				{
					change_var_to_val(token, valid_var(token[i].value + j, shell), j, i);
					//printf("after change_var_val: token[%i].value: %s\n", i, token[i].value);
				}
				j++;
			}
		}
		i++;
	}
}

char	*var_expander_heredoc(t_shell *shell, char	*str)
{
	int	i;

	i = 0;

	while (str[i])
	{
		if (str[i] ==  '$'
			&&  is_spertor(str[i + 1]) ==  false
			&&  str[i + 1]  != '"'  &&  str[i + 1] != '\'')
			str = replace_str_heredoc(str,
					valid_var(str + i, shell), i);
		else
			i++;
	}
	return(str);
}