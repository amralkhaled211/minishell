/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:25:01 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/05 19:30:14 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static int	update_dir(t_shell *shell, char *wd)
{
	set_var(shell, "OLDPWD", get_env_var_value(shell->env, "PWD"));
	set_var(shell, "PWD", wd);
	if (shell->old_dir)
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

static int	change_dir(t_shell *shell, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (cmd_printf("cd", path, "No such file or directory", 1), 1);
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

int	cd(t_shell *shell, char **args)
{
	char	*path;

	if (!args || !args[0] || ft_isspace(args[0][0]) || args[0][0] == '\0'
		|| ft_strncmp(args[0], "--", 3) == 0)
	{
		path = get_env_var_value(shell->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (cmd_printf("cd", NULL, "HOME not set", 1));
		return (change_dir(shell, path));
	}
	if (args[1])
		return (cmd_printf("cd", NULL, "too many arguments", 1));
	if (ft_strncmp(args[0], "-", 2) == 0)
	{
		path = get_env_var_value(shell->env, "OLDPWD");
		if (!path)
			return (cmd_printf("cd", NULL, "OLDPWD not set", 1));
		return (change_dir(shell, path));
	}
	return (change_dir(shell, args[0]));
}
