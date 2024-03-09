/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:53:55 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/11 12:19:47 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	set_var(t_shell *shell,  char *key, char *value)
{
	int	ind;
	char	*tmp;

	ind = get_var_ind(shell->env, key);
	if (value == NULL)
		value  = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return(false);
	if (ind != -1 && shell->env[ind])
	{
		free(shell->env[ind]);
		shell->env[ind] = ft_strjoin(key, tmp);
	}
	else
	{
		ind = get_var_count(shell->env);
		shell->env = realloc_env_var(shell, ind + 1);
		if (!shell->env)
			return(false);
		shell->env[ind] = ft_strjoin(key, tmp);
	}
	free(tmp);
	return(true);
}

void	free_arry(char **arry)
{
	int	i;

	i = 0;
	if (arry)
	{
		while (arry[i])
		{
			if (arry[i])
			{
				free(arry[i]);
				arry[i] = NULL;
			}
			i++;
		}
		free(arry);
		arry = NULL;
	}
}

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	errno = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}