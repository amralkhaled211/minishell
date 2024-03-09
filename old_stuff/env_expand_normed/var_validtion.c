/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_validtion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:47:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/06 13:56:28 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*get_the_var(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;

	start = mini_get_var(str);
	len = var_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (free(var), NULL);
	free(var);
	var = tmp;
	return (var);
}

int	mini_get_var(char *str)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	return (start);
}

bool	is_var_val(char *var, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, len) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

static char	*get_value_from_var(char *var, t_shell *shell)//protect
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, len) == 0)
			break ;
		i++;
	}
	str = ft_strdup(shell->env[i] + len);
	if (!str)
		return (NULL);
	return (str);
}

char	*valid_var(char *str, t_shell *shell)//protect
{
	char	*value;
	char	*var;

	errno = 0;
	var = get_the_var(str);
	if (!var)
		return (NULL);
	if (var && is_var_val(var, shell) == true)
	{
		value = get_value_from_var(var, shell);
		if (!value)
			return (free(var), NULL);
	}
	else if (var && var[0] == '?')
	{
		value = ft_itoa(shell->exit_status + g_exit);
		if (!value)
			return (free(var), NULL);
	}
	else
		value = NULL;
	free(var);
	return (value);
}
