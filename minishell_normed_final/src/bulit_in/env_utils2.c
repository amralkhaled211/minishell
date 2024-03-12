/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:53:55 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/09 18:17:31 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	mini_set_var(t_shell *shell, char *key, char *tmp)
{
	int		ind;
	char	**tmp2;

	ind = get_var_count(shell->env);
	tmp2 = realloc_env_var(shell, ind + 1);
	if (!tmp2)
		return (-1);
	shell->env = tmp2;
	shell->env[ind] = ft_strjoin(key, tmp);
	if (!shell->env[ind])
		return (-1);
	return (0);
}

int	set_var(t_shell *shell, char *key, char *value)
{
	int		ind;
	char	*tmp;

	ind = get_var_ind(shell->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (-1);
	if (ind != -1 && shell->env[ind])
	{
		free(shell->env[ind]);
		shell->env[ind] = ft_strjoin(key, tmp);
		if (!shell->env[ind])
			return (free(tmp), -1);
	}
	else
	{
		if (mini_set_var(shell, key, tmp) == -1)
			return (free(tmp), -1);
	}
	free(tmp);
	return (0);
}

bool	set_export_var_no_value(t_shell *shell, char *key)
{
	int		ind;
	char	**tmp;

	errno = 0;
	ind = get_var_count(shell->export);
	tmp = realloc_export_var(shell, ind + 1);
	if (!tmp)
	{
		free_after_malloc_fail(shell, -1, 5);
		return (false);
	}
	shell->export = tmp;
	shell->export[ind] = ft_strdup(key);
	if (shell->export[ind] == NULL && errno != 0)
		free_after_malloc_fail(shell, -1, 5);
	return (true);
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
