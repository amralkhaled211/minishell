/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:57:35 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/11 17:02:30 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_spertor(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	return (false);
}

bool	range_quotes(char *str, int j)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	i = -1;
	in_squote = false;
	in_dquote = false;
	if (str[j] != '$')
		return (true);
	while (str[++i])
	{
		if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '$' && i == j)
		{
			if (in_squote)
				return (true);
		}
	}
	return (false);
}

void	expander(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i].type != TOKEN_END && token[i].type != TOKEN_DEFAULT)
	{
		if (token[i].type == TOKEN_WORD)
		{
			j = 0;
			if (i > 0 && token[i - 1].type == TOKEN_HEREDOC)
			{
				i ++;
				continue ;
			}
			if (i > 0 && token[i].value[j] == '$' && is_redir(token[i - 1])
				&& !is_var_val(token[i].value + 1, shell))
				token[i].amb_redir = true;
			expand_checker(shell, token, i);
		}
		i++;
	}
}

void	expand_checker(t_shell *shell, t_token *token, int i)
{
	int	j;

	j = 0;
	while (token[i].value && token[i].type != TOKEN_END
		&& token[i].value[j] && token[i].amb_redir == false)
	{
		if (token[i].value[j] == '$'
			&& is_spertor(token[i].value[j + 1]) == false
			&& range_quotes(token[i].value, j) == false
			&& inside_dquote(shell, token[i].value, j) == false)
		{
			if (change_var_to_val(token,
					valid_var(token[i].value + j, shell), j, i) == 1)
			{
				free_after_malloc_fail(shell, -1, 2);
			}
			j = -1;
		}
		j++;
	}
}

char	*get_var_only(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}
