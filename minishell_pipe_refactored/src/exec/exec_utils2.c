/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:04:48 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/14 14:32:17 by aismaili         ###   ########.fr       */
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
		if (g_exit == 0)
			shell->exit_status = 1;
		else
			shell->exit_status = 0;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
	if (dup2(shell->command[i].last_in.i_o_fd, STDIN_FILENO) < 0)
	{
		clean_exec_part(pfd, NULL, true);
		shell->exit_status = 1;
		free_before_exit(shell);
	}
	close(shell->command[i].last_in.i_o_fd);
	shell->command[i].last_in.i_o_fd = -1;
	if (pfd[f][0] != -1)
		close(pfd[f][0]);
	pfd[f][0] = -1;
}

void	output_redir_handler(t_shell *shell, int **pfd, int i)
{
	char	*buffer;
	int	f;

	f = 0;
	if (i % 2 != 0)
		f = 1;
	if (shell->command[i].no_file || shell->command[i].p_err_msg)
	{
		if (!shell->command[i].p_err_msg)
		{
			buffer = malloc(ft_strlen(shell->command[i].last_out.file) + 50);
			my_sprintf(buffer, "minishell: %s: No such file or directory\n",
				shell->command[i].last_out.file);
			write(2, buffer, ft_strlen(buffer));
			free(buffer);
		}
		shell->exit_status = 1;
		clean_exec_part(pfd, NULL, true);
		free_before_exit(shell);
	}
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

void	file_error_handling(t_shell *shell, int **pfd, int i)
{
	char	*buffer;

	shell->exit_status = 1;
	clean_exec_part(pfd, NULL, true);
	if (!shell->command[i].path)
	{
		buffer = malloc(ft_strlen(shell->command[i].cmd_name) + 46);
		if (!buffer)
			free_before_exit(shell);
		my_sprintf(buffer, "%s: command not found\n",
			shell->command[i].cmd_name);
	}
	else
	{
		buffer = malloc(ft_strlen(shell->command[i].path) + 46);
		if (!buffer)
			free_before_exit(shell);
		my_sprintf(buffer, "minishell: %s: No such file or directory\n",
			shell->command[i].path);
	}
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 127;
	free_before_exit(shell);
}

void	file_not_exec(t_shell *shell, int **pfd, int i)
{
	char	*buffer;
	int		j;

	j = 0;
	buffer = malloc(ft_strlen(shell->command[i].cmd_name) + 40);
	my_sprintf(buffer, "minishell: %s: Permission denied\n",
		shell->command[i].path);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 126;
	clean_exec_part(pfd, NULL, true);
	free_before_exit(shell);
}

void	is_a_dir(t_shell *shell, int **pfd, int i)
{
	char	*buffer;

	buffer = malloc(ft_strlen(shell->command[i].path) + 40);
	my_sprintf(buffer, "minishell: %s: Is a directory\n",
		shell->command[i].path);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 126;
	clean_exec_part(pfd, NULL, shell->num_pipes);
	free_before_exit(shell);
}
