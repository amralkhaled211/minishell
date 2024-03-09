/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:43:46 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/08 15:21:30 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	var_len(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_var_compliant(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

static bool	help_inside_dquote(t_shell *shell, char *t_value, int i)
{
	char	*tmp_var;

	tmp_var = NULL;
	i++;
	if (!ft_isalnum(t_value[i]) && t_value[i] != '?')
		return (true);
	tmp_var = get_var_only(t_value);
	if (!tmp_var)
		free_after_malloc_fail(shell, -1, 2);
	if (!is_var_val(tmp_var, shell))
		return (free(tmp_var), false);
	else
		return (free(tmp_var), false);
}

bool	inside_dquote(t_shell *shell, char *t_value, int j)
{
	int		i;
	bool	inside_dquote;

	i = 0;
	inside_dquote = false;
	if (!t_value || t_value[j] != '$')
		return (false);
	while (t_value[i])
	{
		if (t_value[i] == '"')
			inside_dquote = !inside_dquote;
		if (inside_dquote && i == j)
		{
			return (help_inside_dquote(shell, t_value, i));
		}
		i++;
	}
	return (false);
}
