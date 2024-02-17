/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:11:20 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/07 18:06:34 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"
#include <limits.h>

bool	init_dir(t_shell *shell) // i put this function in the init_all_shell  function this is very required in  my cd function
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	shell->current_dir = ft_strdup(wd);
	if (!shell->current_dir)
		return (false);
	if (get_var_ind(shell->env, "OLDPWD") != -1)
	{
		shell->old_dir = ft_strdup(get_env_var_value(shell->env,
					"OLDPWD"));
		if (!shell->old_dir)
			return (false);
	}
	else
	{
		shell->old_dir = ft_strdup(wd);
		if (!shell->old_dir)
			return (false);
	}
	return (true);
}
