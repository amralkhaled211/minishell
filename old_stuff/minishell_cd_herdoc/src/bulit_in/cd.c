/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:25:01 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/07 18:33:45 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int  ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static void update_dir(t_shell *shell, char *wd)
{
    set_var(shell, "OLDPWD",get_env_var_value(shell->env, "PWD"));
    set_var(shell, "PWD", wd);
	if (shell->old_dir)
	{
		free(shell->old_dir);
		shell->old_dir = ft_strdup(shell->current_dir);
	}
	if (shell->current_dir)
	{
		free(shell->current_dir);
		shell->current_dir = ft_strdup(wd);
	}
    free(wd);
}

static bool change_dir(t_shell *shell, char *path)
{
    char    *ret;
    char    *tmp;
    char    cwd[PATH_MAX];

    ret = NULL;
    if(chdir(path) != 0)
        return(printf("no such file or directory\n"), false);
    ret = getcwd(cwd, PATH_MAX);
    if (!ret)
    {
        printf("cd: error retrieving current directory\n");
        ret = ft_strjoin(shell->current_dir, "/");
        tmp = ret;
        ret = ft_strjoin(tmp, path);
        free(tmp);
    }
    else
    ret = ft_strdup(cwd);
    update_dir(shell, ret);
    return (true);
}

int cd(t_shell *shell, char **args)
{
    char *path;

    if (!args || !args[0] || ft_isspace(args[0][0]) || args[0][0] == '\0'
		|| ft_strncmp(args[0], "--", 3) == 0)
    {
        path = get_env_var_value(shell->env, "HOME");
        if (!path || *path == '\0' || ft_isspace(*path))
            return(printf("HOME is not set\n"), 1);
        return(!change_dir(shell, path));
    }
    if (args[1])
        return(printf("to Many arguments\n"), 1);
    if (ft_strncmp(args[0], "-", 2) == 0)
    {
        path = get_env_var_value(shell->env, "OLDPWD");
        if (!path)
            return(printf("OLDPWD not set\n"), 1);
        return(!change_dir(shell, path));
    }
    return(!change_dir(shell, args[0]));
}