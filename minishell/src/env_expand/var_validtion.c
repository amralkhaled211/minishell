/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_validtion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:47:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/03 15:24:55 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	*get_the_var(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

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
	len = var_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free(var);
	var = tmp;
	return (var);
}

static bool	is_var_val(char *var, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var, len) == 0)
			return (true);
		i++;
	}
	return (false);
}

static char	*get_value_from_var(char *var, t_shell *shell)
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
	return (str);
}

char *valid_var(char *str, t_shell *shell)
{
	char *value;
	char *var;

	var = get_the_var(str);
	if (var &&  is_var_val(var, shell) == true)
	{
		value = get_value_from_var(var, shell);
	}
	/* else if (var && var[0] == '?')
		value = */
	else
		value = NULL;
	free(var);
	return(value);
}