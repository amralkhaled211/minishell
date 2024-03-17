/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:00:32 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/12 12:32:03 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static void	set_all_values(t_shell *shell, char *wd)
{
	if (set_var(shell, "OLDPWD", get_env_var_value(shell->env, "PWD")) != 0)
		free_after_malloc_fail(shell, -1, 5);
	if (set_export_var_with_value(shell, "OLDPWD",
			get_env_var_value(shell->env, "PWD")) == -1)
		free_after_malloc_fail(shell, -1, 5);
	if (set_var(shell, "PWD", wd) != 0)
		free_after_malloc_fail(shell, -1, 5);
	if (set_export_var_with_value(shell, "PWD", wd) == -1)
		free_after_malloc_fail(shell, -1, 5);
}

static int	update_dir(t_shell *shell, char *wd)
{
	set_all_values(shell, wd);
	{
		free(shell->old_dir);
		shell->old_dir = ft_strdup(shell->current_dir);
		if (!shell->old_dir)
			return (-2);
	}
	if (shell->current_dir)
	{
		free(shell->current_dir);
		shell->current_dir = ft_strdup(wd);
		if (!shell->current_dir)
			return (-2);
	}
	free(wd);
	return (0);
}

int	change_dir(t_shell *shell, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (cmd_printf("cd", path, "No such file or directory", 1));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		cmd_printf("cd", path, "error retrieving current directory", 1);
		ret = ft_strjoin(shell->current_dir, "/");
		if (!ret)
			return (-2);
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		if (!ret)
			return (free(tmp), -2);
		free(tmp);
	}
	else
		ret = ft_strdup(cwd);
	if (update_dir(shell, ret) == -2)
		return (-2);
	return (0);
}
