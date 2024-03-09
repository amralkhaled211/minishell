/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:52:50 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/05 19:32:20 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static bool	is_with_flag(char *av)
{
	int	i;

	i = 0;
	if (av[i] != '-')
		return (false);
	i++;
	while (av[i] && av[i] == 'n')
		i++;
	if (av[i] == '\0')
		return (true);
	return (false);
}

static void	print_args(char **args, bool n_flag, int i, t_shell *shell)
{
	char	*tmp;

	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i])
	{
		if (args[i][0] == '~' && args[i][1] == '\0')
		{
			tmp = get_env_var_value(shell->env, "HOME");
			if (!tmp)
				free_after_malloc_fail(shell, -1, 5);
			ft_putstr_fd(tmp, 1);
		}
		else
			ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', 1);
		i++;
	}
}

int	echo(char **args, t_shell *shell)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	while (args[i] && is_with_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	print_args(args, n_flag, i, shell);
	return (0);
}
