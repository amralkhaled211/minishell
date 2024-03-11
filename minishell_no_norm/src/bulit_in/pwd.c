/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:26 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/11 16:06:56 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pwd(t_shell *shell, char **args)
{
	char	buffer[4096];
	char	*cwd;

	if (args && args[0] && args[0][0] == '-')
	{
		if (cmd_printf("pwd", args[0], "invalid option", 2) == -3)
			free_after_malloc_fail(shell, -1, 5);
		return(2);
	}
	if (shell->current_dir)
	{
		ft_putendl_fd(shell->current_dir, 1);
		return (0);
	}
	cwd = getcwd(buffer, 4096);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	if (cmd_printf("pwd", NULL, strerror(errno), errno) == -3)
		free_after_malloc_fail(shell, -1, 5);
	return (1);
}
