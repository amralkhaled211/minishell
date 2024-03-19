/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:03:26 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/17 11:06:14 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_env_fail(t_shell *shell, int m)
{
	int	i;

	perror("malloc failed");
	if (m == -1)
		exit(1);
	i = 0;
	while (i < m)
		free(shell->env[i++]);
	exit(1);
}

void	free_split_fail(t_split *split, int a)
{
	int	i;

	i = 0;
	while (i < a)
	{
		free(split->result[i]);
		i++;
	}
	free(split->result);
}

void	free_after_malloc_fail(t_shell *shell, int f, int stage)
{
	shell->exit_status = 1;
	if (stage == 1)
		free_malloc_fail_stage_1(shell, f);
	if (stage == 2)
		free_malloc_fail_stage_2(shell, f);
	if (stage == 3)
		free_malloc_fail_stage_3(shell, f);
	if (stage == 4)
		free_malloc_fail_stage_4(shell, f);
	if (stage == 5)
		free_malloc_fail_stage_5(shell, f);
	exit(shell->exit_status % 256);
}

void	free_before_exit(t_shell *shell)
{
	close_fds(shell);
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	free_token_array(shell->token);
	free_token_array(shell->n_token);
	free_cmd_table(shell, shell->command, -1);
	free(shell->current_dir);
	free(shell->old_dir);
	exit((shell->exit_status) % 256);
}

void	close_fds(t_shell *shell)
{
	if (shell->stdin_backup == -1 && shell->stdout_backup == -1)
		return ;
	if (dup2(shell->stdin_backup, 0) == -1)
	{
		if (dup2(shell->stdout_backup, 1) == -1)
			return ;
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
		return ;
	}
	if (dup2(shell->stdout_backup, 1) == -1)
	{
		close(shell->stdin_backup);
		shell->stdout_backup = -1;
		return ;
	}
	close(shell->stdin_backup);
	shell->stdin_backup = -1;
	close(shell->stdout_backup);
	shell->stdout_backup = -1;
}
