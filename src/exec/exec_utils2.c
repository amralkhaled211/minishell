/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:48 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 14:13:18 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	input_redir_handler(t_shell *shell, int **pfd, int i)
{
	int	f;

	f = 0;
	if (i % 2 == 0)
		f = 1;
	if (shell->command[i].no_file || shell->command[i].p_err_msg)
	{
		if (shell->command[i].cmd_name)
			shell->exit_status = 1;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
	if (dup2(shell->command[i].last_in.i_o_fd, STDIN_FILENO) < 0)
	{
		clean_exec_part(pfd, NULL, true);
		if (shell->command[i].cmd_name)
			shell->exit_status = 1;
		free_before_exit(shell);
	}
	close(shell->command[i].last_in.i_o_fd);
	shell->command[i].last_in.i_o_fd = -1;
	if (pfd[f][0] != -1)
		close(pfd[f][0]);
	pfd[f][0] = -1;
}

static void	output_redir_handler2(t_shell *shell, int **pfd, int i)
{
	char	*buffer;

	if (!shell->command[i].p_err_msg)
	{
		buffer = malloc(ft_strlen(shell->command[i].last_out.file) + 60);
		if (!buffer)
		{
			clean_exec_part(pfd, NULL, true);
			free_after_malloc_fail(shell, -1, 5);
		}
		my_sprintf(buffer, "minishell: %s: No such file or directory\n",
			shell->command[i].last_out.file);
		write(2, buffer, ft_strlen(buffer));
		free(buffer);
	}
	shell->exit_status = 1;
	clean_exec_part(pfd, NULL, true);
	free_before_exit(shell);
}

void	output_redir_handler(t_shell *shell, int **pfd, int i)
{
	int	f;

	f = 0;
	if (i % 2 != 0)
		f = 1;
	if (shell->command[i].no_file || shell->command[i].p_err_msg)
		output_redir_handler2(shell, pfd, i);
	if (dup2(shell->command[i].last_out.i_o_fd, STDOUT_FILENO) < 0)
	{
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
	close(shell->command[i].last_out.i_o_fd);
	shell->command[i].last_out.i_o_fd = -1;
	if (pfd[f][1] != -1)
		close(pfd[f][1]);
	pfd[f][1] = -1;
}

void	file_not_exec(t_shell *shell, int **pfd, int i)
{
	char	*buffer;
	char	*path_env;

	buffer = NULL;
	clean_exec_part(pfd, NULL, true);
	errno = 0;
	path_env = get_env_var_value(shell->env, "PATH");
	if (!path_env && errno != 0)
		free_after_malloc_fail(shell, 0, 5);
	if (!path_env && !shell->command[i].is_path)
	{
		buffer = malloc(ft_strlen(shell->command[i].cmd_name) + 40);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer, "minishell: %s: Permission denied\n",
			shell->command[i].cmd_name);
	}
	else
		buffer = file_not_exec2(shell, i);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 126;
	free_before_exit(shell);
}
