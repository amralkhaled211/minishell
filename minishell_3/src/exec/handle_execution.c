/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:02:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/17 18:00:02 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	clean_before_exec(pid_t *child_pid, int **pfd, int i)
{
	free(child_pid);
	if (i % 2 == 0 && pfd[0][0] != -1)
	{
		close(pfd[0][0]);
		pfd[0][0] = -1;
	}
	if (i % 2 == 0 && pfd[1][1] != -1)
	{
		close(pfd[1][1]);
		pfd[1][1] = -1;
	}
	if (i % 2 != 0 && pfd[1][0] != -1)
	{
		close(pfd[1][0]);
		pfd[1][0] = -1;
	}
	if (i % 2 != 0 && pfd[0][1] != -1)
	{
		close(pfd[0][1]);
		pfd[0][1] = -1;
	}
}

static void	dup_std_in(t_shell *shell, int **pfd, int i)
{
	int	f;

	f = 0;
	if (i % 2 == 0)
		f = 1;
	if (dup2(pfd[f][0], STDIN_FILENO) < 0)
	{
		perror("dup2 fail (input)");
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
	if (pfd[f][0] != -1)
		close(pfd[f][0]);
	pfd[f][0] = -1;
}

static void	dup_std_out(t_shell *shell, int **pfd, int i)
{
	int	f;

	f = 0;
	if (i % 2 != 0)
		f = 1;
	if (dup2(pfd[f][1], STDOUT_FILENO) < 0)
	{
		perror("dup2 fail (output)");
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
	if (pfd[f][1] != -1)
		close(pfd[f][1]);
	pfd[f][1] = -1;
}

void	main_exec_child(t_shell *shell, pid_t *child_pid, int **pfd, int i)
{
	clean_before_exec(child_pid, pfd, i);
	if (i == shell->num_pipes)
	{
		if (pfd[0][1] != -1)
			close(pfd[0][1]);
		pfd[0][1] = -1;
		if (pfd[1][1] != -1)
			close(pfd[1][1]);
		pfd[1][1] = -1;
	}
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
	else if (!shell->command[i].is_built_in && shell->command[i].path
		&& access(shell->command[i].path, X_OK) != 0)
		file_not_exec(shell, pfd, i);
	mini_handle_exec(shell, pfd, i);
}

void	mini_handle_exec(t_shell *shell, int **pfd, int i)
{
	clean_exec_part(pfd, NULL, true);
	if (shell->command[i].is_built_in)
	{
		execute_built_in(shell, &shell->command[i]);
		free_before_exit(shell);
	}
	if (shell->command[i].cmd_name && is_directory(shell->command[i].path))
		is_a_dir(shell, pfd, i);
	if (!shell->command[i].is_built_in && shell->command[i].cmd_name)
	{
		close_all_fds(shell);
		signal(SIGPIPE, SIG_DFL);
		if (execve(shell->command[i].path, shell->command[i].cmd_args,
				shell->env) != 0)
			perror("execve");
		free_before_exit(shell);
	}
	free_before_exit(shell);
}
