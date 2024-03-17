/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:14 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 18:34:12 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	restore_std(t_shell *shell)
{
	if (dup2(shell->stdin_backup, STDIN_FILENO) == -1)
		free_after_malloc_fail(shell, -1, 5);
	if (dup2(shell->stdout_backup, STDOUT_FILENO) == -1)
		free_after_malloc_fail(shell, -1, 5);
	close(shell->stdin_backup);
	shell->stdin_backup = -1;
	close(shell->stdout_backup);
	shell->stdout_backup = -1;
}

int	single_built_in(t_shell *shell, t_command *command)
{
	if (shell->num_pipes == 0 && command[0].is_built_in)
	{
		shell->stdin_backup = dup(STDIN_FILENO);
		shell->stdout_backup = dup(STDOUT_FILENO);
		if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
			free_after_malloc_fail(shell, -1, 5);
		if (prep_redir(shell, command, 0) != 1)
			execute_built_in(shell, &command[0]);
		restore_std(shell);
		return (1);
	}
	return (0);
}

int	prep_redir(t_shell *shell, t_command *command, int i)
{
	(void)shell;
	if (command[i].last_in.file)
	{
		if (command[i].no_file == true || command[i].p_err_msg == true)
			return (1);
		if (dup2(command[i].last_in.i_o_fd, STDIN_FILENO) < 0)
		{
			shell->exit_status = 1;
			free_after_malloc_fail(shell, -1, 5);
		}
		close(command[i].last_in.i_o_fd);
	}
	if (command[i].last_out.file)
	{
		if (command[i].p_err_msg == true)
			return (1);
		if (dup2(command[i].last_out.i_o_fd, STDOUT_FILENO) < 0)
		{
			shell->exit_status = 1;
			free_after_malloc_fail(shell, -1, 5);
		}
		close(command[i].last_out.i_o_fd);
	}
	return (0);
}
