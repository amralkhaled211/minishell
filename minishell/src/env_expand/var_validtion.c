/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_validtion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:47:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/10 15:34:52 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	*get_the_var(char *str)//protect
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
	if (!tmp)//we have to exit now, because in the next we would also acceept a NULL
		return (NULL);
	free(var);
	var = tmp;
	return (var);
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
	if (!str)//we have to exit, when strdup fails
		return (NULL);
	return (str);
}

char	*valid_var(char *str, t_shell *shell)//protect
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
