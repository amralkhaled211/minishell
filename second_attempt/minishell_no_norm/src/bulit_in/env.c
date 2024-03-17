/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:51:20 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/11 16:02:57 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args && args[0]&& args[0][0] == '-')
	{
		if (cmd_printf("env", "invalid option", args[0], 125) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return(125);
	}
	if (args && args[0])
	{
		if (cmd_printf("env", args[0], "No such file or directory", 127) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return (127);
	}
	if (!shell->env)
	{
		return (1);
	}
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], 1);
	return (0);
}
