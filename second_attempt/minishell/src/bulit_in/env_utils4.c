/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:34:39 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 15:37:12 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_valid_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	**realloc_env_var(t_shell *shell, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(char **));
	if (!new_env)
		return (NULL);
	i = 0;
	while (shell->env[i] && i < size)
	{
		new_env[i] = ft_strdup(shell->env[i]);
		free(shell->env[i]);
		i++;
	}
	free(shell->env);
	return (new_env);
}

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
