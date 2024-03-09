/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:51:20 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/05 16:26:36 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	if (args && args[0])
	{
		ft_putendl_fd("env : too many arguments!!", 2);
		return(1);
	}
	if (!shell->env)
	{
		ft_putendl_fd("env : does not exsit", 2);
		return (1);
	}
	while (shell->env[i])
		ft_putendl_fd(shell->env[i++], 1);
	return(0);
}