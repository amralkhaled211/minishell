/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:53:55 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/06 15:35:54 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*make_qoutes(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(str) + 3;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	new[i] = '\"';
	i++;
	while (str[j])
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\"';
	i++;
	new[i] = '\0';
	return (new);
}

static int	mini_set_with_value(t_shell *shell, char *key, char *tmp)
{
	int		ind;
	char	**tmp2;

	ind = get_var_count(shell->export);
	tmp2 = realloc_export_var(shell, ind + 1);
	if (!shell->export)
		return (-1);
	shell->export = tmp2;
	shell->export[ind] = ft_strjoin(key, tmp);
	if (!shell->export[ind])
		return (-1);
	return (0);
}

int	set_export_var_with_value(t_shell *shell, char *key, char *value)//normed
{
	int		ind;
	char	*tmp;
	char	*tmp1;

	ind = get_export_var_ind(shell->export, key);
	if (value == NULL)
		value = "";
	tmp1 = make_qoutes(value);
	if (!tmp1)
		return (-1);
	tmp = ft_strjoin("=", tmp1);
	if (!tmp)
		return (free(tmp1), -1);
	if (ind != -1 && shell->export[ind])
	{
		free(shell->export[ind]);
		shell->export[ind] = ft_strjoin(key, tmp);
		if (!shell->export[ind])
			return (free(tmp), free(tmp1), -1);
	}
	else
		if (mini_set_with_value(shell, key, tmp) == -1)
			return (free(tmp), free(tmp1), -1);
	return (free(tmp), free(tmp1), 0);
}

static int	mini_set_var(t_shell *shell, char *key, char *tmp)
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

	ind = get_var_count(shell->export);
	tmp = realloc_export_var(shell, ind + 1);
	if (!tmp)
		free_after_malloc_fail(shell, -1, 5);
	shell->export = tmp;
	shell->export[ind] = ft_strdup(key);
	if (shell->export[ind] == NULL)
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
