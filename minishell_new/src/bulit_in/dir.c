/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:11:20 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/05 19:30:34 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"
#include <limits.h>

bool	init_dir(t_shell *shell)
{
	char	buff[PATH_MAX];
	char	*wd;

	errno = 0;
	wd = getcwd(buff, PATH_MAX);
	shell->current_dir = ft_strdup(wd);
	if (!shell->current_dir && errno != 0)
		return (free_dir_fail(shell, 1), false);
	if (get_var_ind(shell->env, "OLDPWD") != -1)
	{
		errno = 0;
		shell->old_dir = ft_strdup(get_env_var_value(shell->env,
					"OLDPWD"));
		if (!shell->old_dir && errno != 0)
			return (free_dir_fail(shell, 2), false);
	}
	else
	{
		errno = 0;
		shell->old_dir = ft_strdup(wd);
		if (!shell->old_dir && errno != 0)
			return (free_dir_fail(shell, 2), false);
	}
	return (true);
}

void	free_dir_fail(t_shell *shell, int stage)
{
	free_str_array(shell->env);
	free_str_array(shell->export);
	if (stage == 1)
		exit (1);
	else if (stage == 2)
		free(shell->current_dir);
	exit (1);
}
