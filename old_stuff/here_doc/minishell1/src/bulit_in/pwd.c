/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:26 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/07 18:07:27 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	pwd(t_shell *shell)
{
	char	buffer[4096];
	char	*cwd;

	(void)shell;
	/* if (shell->current_dir)
	{
		ft_putendl_fd(shell->current_dir, 1);
		return (0);
	} */
	cwd = getcwd(buffer, 4096);
	if (cwd)
	{
		ft_putendl_fd(cwd, 1);
		return(0);
	}
	ft_putendl_fd("PWD FAILED", 2);
	return(1);
}