/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:48:25 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/08 15:35:47 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_rest_export(char **new_env, int i)
{
	int	a;

	a = 0;
	while (a < i)
		free(new_env[a++]);
	free(new_env);
}

char	**realloc_export_var(t_shell *shell, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char **));
	if (!new_env)
		return (NULL);
	i = 0;
	while (shell->export[i] && i < size)
	{
		new_env[i] = ft_strdup(shell->export[i]);
		if (new_env[i] == NULL)
		{
			free_rest_export(new_env, i);
			return (NULL);
		}
		free(shell->export[i]);
		i++;
	}
	free(shell->export);
	return (new_env);
}

int	get_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	get_var_ind(char **env, char *var)
{
	int		i;
	char	*tmp;

	errno = 0;
	tmp = ft_strjoin(var, "=");
	if (!tmp && errno != 0)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}

int	get_export_var_ind(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(var);
	if (!tmp)
		return (-2);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free(tmp);
			return (i);
		}
		i++;
	}
	free(tmp);
	return (-1);
}
