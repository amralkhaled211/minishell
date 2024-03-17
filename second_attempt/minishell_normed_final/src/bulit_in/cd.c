/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:25:01 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/12 12:12:01 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	validate_cd_args(char **args)
{
	if (!args || !args[0] || ft_isspace(args[0][0]) || args[0][0] == '\0'
		|| ft_strncmp(args[0], "--", 3) == 0)
	{
		return (1);
	}
	return (0);
}

static int	handle_home_not_set(t_shell *shell)
{
	char	*path;

	path = get_env_var_value(shell->env, "HOME");
	if (!path || *path == '\0' || ft_isspace(*path))
	{
		if (cmd_printf("cd", NULL, "HOME not set", 1) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return (1);
	}
	return (change_dir(shell, path));
}

static int	handle_too_many_arguments(t_shell *shell)
{
	if (cmd_printf("cd", NULL, "too many arguments", 1) == -3)
		free_after_malloc_fail(shell, -1, 5);
	return (1);
}

static int	handle_oldpwd_not_set(t_shell *shell)
{
	char	*path;

	path = get_env_var_value(shell->env, "OLDPWD");
	if (!path)
	{
		if (cmd_printf("cd", NULL, "OLDPWD not set", 1) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return (1);
	}
	return (change_dir(shell, path));
}

int	cd(t_shell *shell, char **args)
{
	if (validate_cd_args(args))
		return (handle_home_not_set(shell));
	if (args[1])
		return (handle_too_many_arguments(shell));
	if (ft_strncmp(args[0], "-", 2) == 0)
		return (handle_oldpwd_not_set(shell));
	return (change_dir(shell, args[0]));
}
