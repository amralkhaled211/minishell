/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_amb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:21:46 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 21:22:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_only_spaces(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!ft_strchr(" \t", value[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	is_multiple_words(char *trmd)
{
	int		i;

	i = 0;
	while (trmd[i])
	{
		if (ft_strchr(" \t", trmd[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	check_amb_rules(t_shell *shell, char *value)
{
	char	*trmd;

	if (is_only_spaces(value))
		return (true);
	trmd = ft_strtrim(value, " \t");
	if (!trmd)
		free_after_malloc_fail(shell, -1, 2);
	if (is_multiple_words(trmd))
		return (free(trmd), true);
	return (free(trmd), false);
}

void	check_amb(t_shell *shell, t_token *token)
{
	char	*var;
	char	*value;

	var = get_the_var(token->value);
	if (!var)
		free_after_malloc_fail(shell, -1, 2);
	if (!is_var_val(var, shell))
	{
		token->amb_redir = true;
		free(var);
		return ;
	}
	value = get_value_from_var(var, shell);
	if (!value)
		free_after_malloc_fail(shell, -1, 2);
	if (check_amb_rules(shell, value))
	{
		token->amb_redir = true;
		free(value);
		free(var);
		return ;
	}
	free(value);
	free(var);
}
