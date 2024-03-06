/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:26 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/06 13:41:12 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pwd(t_shell *shell)
{
	char	buffer[4096];
	char	*cwd;

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
