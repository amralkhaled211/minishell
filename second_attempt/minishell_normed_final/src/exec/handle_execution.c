/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:02:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/07 14:54:11 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	clean_before_exec(t_shell *shell, pid_t *child_pid, int *pfd, int i)
{
	int	j;

	free(child_pid);
	(void)child_pid;
	j = 0;
	while (j < shell->num_pipes * 2)
	{
		if (j != ((i - 1) * 2) && j != (i * 2 + 1) && pfd[j] != -1)
		{
			close(pfd[j]);
			pfd[j] = -1;
		}
		j++;
	}
}

static void	dup_std_in(t_shell *shell, int *pfd, int i)
{
	if (dup2(pfd[(i - 1) * 2], STDIN_FILENO) < 0)
	{
		perror("dup2 fail (input)");
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, shell->num_pipes);
		free_before_exit(shell);
	}
	close(pfd[(i - 1) * 2]);
	pfd[(i - 1) * 2] = -1;
}

static void	dup_std_out(t_shell *shell, int *pfd, int i)
{
	if (dup2(pfd[i * 2 + 1], STDOUT_FILENO) < 0)
	{
		perror("dup2 fail (output)");
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, shell->num_pipes);
		free_before_exit(shell);
	}
	close(pfd[i * 2 + 1]);
	pfd[i * 2 + 1] = -1;
}

void	handle_execution(t_shell *shell, pid_t *child_pid, int *pfd, int i)
{
	c_handle_backslash();
	c_do_signal();
	child_pid[i] = fork();
	if (child_pid[i] == -1)
		free_before_exit(shell);
	else if (child_pid[i] == 0)
	{
		clean_before_exec(shell, child_pid, pfd, i);
		if (shell->command[i].last_in.file)
			input_redir_handler(shell, pfd, i);
		else if (i > 0)
			dup_std_in(shell, pfd, i);
		if (shell->command[i].last_out.file)
			output_redir_handler(shell, pfd, i);
		else if (i < shell->num_pipes)
			dup_std_out(shell, pfd, i);
		if (!shell->command[i].is_built_in && (!shell->command[i].path
				|| access(shell->command[i].path, F_OK) != 0))
			file_error_handling(shell, pfd, i);
		else if (access(shell->command[i].path, X_OK) != 0
			&& !shell->command[i].is_built_in)
			file_not_exec(shell, pfd, i);
		mini_handle_exec(shell, pfd, i);
	}
}

void	mini_handle_exec(t_shell *shell, int *pfd, int i)
{
	(void)pfd;
	if (shell->command[i].is_built_in)
	{
		execute_built_in(shell, &shell->command[i]);
		clean_exec_part(pfd, NULL, shell->num_pipes);
		free_before_exit(shell);
	}
	if (shell->command[i].cmd_name && is_directory(shell->command[i].path))
		is_a_dir(shell, pfd, i);
	if (!shell->command[i].is_built_in && shell->command[i].cmd_name)
	{
		if (execve(shell->command[i].path, shell->command[i].cmd_args,
				shell->env) != 0)
			perror("execve");
		clean_exec_part(pfd, NULL, shell->num_pipes);
		free_before_exit(shell);
	}
	clean_exec_part(pfd, NULL, shell->num_pipes);
	free_before_exit(shell);
	exit (0);
}
