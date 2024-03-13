/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:41:00 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/06 13:42:44 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	delete_var(t_shell *shell, int ind)
{
	int		i;
	int		count;
	char	**tmp;

	if (ind > get_var_count(shell->env))
		return (1);
	free(shell->env[ind]);
	i = ind;
	count = ind;
	while (shell->env[i + 1])
	{
		shell->env[i] = ft_strdup(shell->env[i + 1]);
		if (!shell->env[i])
			return (-2);
		free(shell->env[i + 1]);
		count++;
		i++;
	}
	tmp = realloc_env_var(shell, count);
	if (!tmp)
		return (-2);
	shell->env = tmp;
	return (0);
}

static int	delete_var_export(t_shell *shell, int ind)
{
	int		i;
	int		count;
	char	**tmp;

	if (ind > get_var_count(shell->export))
		return (1);
	free(shell->export[ind]);
	i = ind;
	count = ind;
	while (shell->export[i + 1])
	{
		shell->export[i] = ft_strdup(shell->export[i + 1]);
		if (!shell->export[i])
			return (-2);
		free(shell->export[i + 1]);
		count++;
		i++;
	}
	tmp = realloc_export_var(shell, count);
	if (!tmp)
		return (-2);
	shell->export = tmp;
	return (0);
}

static int	get_var_ind_export(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	unset(t_shell *shell, char **args)
{
	int	i;
	int	ind;
	int	res;

	i = 0;
	res = 0;
	if (args && args[0] && args[0][0] == '-')
	{
		if (cmd_printf("unset", args[0], "invalid option", 2) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return (2);
	}
	while (args[i])
	{
		ind = get_var_ind_export(shell->export, args[i]);
		if (ind != -1)
			res = delete_var_export(shell, ind);
		ind = get_var_ind(shell->env, args[i]);
		if (ind != -1)
			res = delete_var(shell, ind);
		if (res == -2)
			free_after_malloc_fail(shell, -1, 5);
		i++;
	}
	return (0);
}
