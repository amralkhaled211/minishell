/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:17:54 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/11 15:00:41 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	export_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->export)
	{
		return (1);
	}
	while (shell->export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(shell->export[i++], 1);
	}
	return (0);
}

static int	export_env_if_empty(t_shell *shell, char **av)
{
	if (!av[0])
		return (export_env(shell));
	return (0);
}

static int	handle_invalid_identifier(char *command, char *var, int exit_code)
{
	return (cmd_printf(command, var, " not a valid identifier", exit_code));
}

static int	export_variable_with_no_value(t_shell *shell, char *variable)
{
	if (set_export_var_no_value(shell, variable))
		return (1);
	return (0);
}
static int	mini_export(t_shell *shell, char **av, int i, char **arry, int tmp)
{
	while (av[i])
	{
		if (!is_valid_var_key(av[i]))
			return (handle_invalid_identifier("export", av[i], 1));
		else if (ft_strchr(av[i], '=') == NULL)
		{
			tmp = get_export_var_ind(shell->export, av[i]);
			if (tmp == -2)
				free_after_malloc_fail(shell, -1, 5);
			if (tmp == -1 && export_variable_with_no_value(shell, av[i++]))
				continue ;
		}
		else if (ft_strchr(av[i], '=') != NULL)
			help_export(shell, av[i], arry);
		i++;
	}
	return (0);
}

int	export(t_shell *shell, char **av)
{
	int		i;
	int		tmp;
	char	**arry;
	int		res;

	i = 0;
	arry = NULL;
	tmp = 0;
	res = 0;
	if (export_env_if_empty(shell, av) != 0)
		return (0);
	if (av && av[0] && av[0][0] == '-')
		return(cmd_printf("export", av[0], "invalid option", 2));
	res = mini_export(shell, av, i, arry, tmp);
	mini_sort(shell->export, array_len(shell->export));
	return (res);
}
