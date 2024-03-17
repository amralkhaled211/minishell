/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:11:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 13:18:52 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_malloc_fail_stage_1(t_shell *shell, int f)
{
	int	i;

	i = 0;
	shell->exit_status = 1;
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	while (i < f)
		free(shell->token[i++].value);
	free(shell->token);
	free(shell->current_dir);
	free(shell->old_dir);
}

void	free_malloc_fail_stage_2(t_shell *shell, int f)
{
	(void)f;
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	free_token_array(shell->token);
	free(shell->current_dir);
	free(shell->old_dir);
}

void	free_malloc_fail_stage_3(t_shell *shell, int f)
{
	int	i;

	i = 0;
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	free_token_array(shell->token);
	if (f != -1)
	{
		while (i < f)
			free(shell->n_token[i++].value);
		free(shell->n_token);
	}
	else
		free_token_array(shell->n_token);
	free(shell->current_dir);
	free(shell->old_dir);
}

void	free_malloc_fail_stage_4(t_shell *shell, int f)
{
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	free_token_array(shell->token);
	free_token_array(shell->n_token);
	free_cmd_table(shell, shell->command, f);
	free(shell->current_dir);
	free(shell->old_dir);
}

void	free_malloc_fail_stage_5(t_shell *shell, int f)
{
	close_fds(shell);
	free_str_array(shell->splited);
	free_str_array(shell->env);
	free_str_array(shell->export);
	free_token_array(shell->token);
	free_token_array(shell->n_token);
	free_cmd_table(shell, shell->command, f);
	free(shell->current_dir);
	free(shell->old_dir);
}
