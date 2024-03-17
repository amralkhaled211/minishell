/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:26 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/11 15:28:42 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pwd(t_shell *shell, char **args)
{
	char	buffer[4096];
	char	*cwd;

	if (args && args[0] && args[0][0] == '-')
		return(cmd_printf("pwd", args[0], "invalid option", 2));
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
	cmd_printf("pwd", NULL, strerror(errno), errno);
	return (1);
}
