/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:36:29 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 12:42:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	is_a_dir(t_shell *shell, int **pfd, int i)
{
	char	*buffer;

	(void)pfd;
	buffer = malloc(ft_strlen(shell->command[i].path) + 40);
	if (!buffer)
		free_after_malloc_fail(shell, -1, 5);
	my_sprintf(buffer, "minishell: %s: Is a directory\n",
		shell->command[i].path);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 126;
	free_before_exit(shell);
}

void	is_not_a_dir(t_shell *shell, int **pfd, int i)
{
	char	*buffer;

	(void)pfd;
	buffer = malloc(ft_strlen(shell->command[i].path) + 40);
	if (!buffer)
		free_after_malloc_fail(shell, -1, 5);
	my_sprintf(buffer, "minishell: %s: Not a directory\n",
		shell->command[i].path);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 126;
	free_before_exit(shell);
}

void	close_all_fds(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (!shell->command[++i].end_of_cmd)
	{
		if (!shell->command[i].redirections)
			continue ;
		j = -1;
		while (shell->command[i].redirections[++j].file)
		{
			if (shell->command[i].redirections[j].input_fd != -1)
				close(shell->command[i].redirections[j].input_fd);
			shell->command[i].redirections[j].input_fd = -1;
			if (shell->command[i].redirections[j].output_fd != -1)
				close(shell->command[i].redirections[j].output_fd);
			shell->command[i].redirections[j].output_fd = -1;
		}
	}
}

char	*file_not_exec2(t_shell *shell, int i)
{
	char	*buffer;

	buffer = malloc(ft_strlen(shell->command[i].path) + 40);
	if (!buffer)
		free_after_malloc_fail(shell, -1, 5);
	my_sprintf(buffer, "minishell: %s: Permission denied\n",
		shell->command[i].path);
	return (buffer);
}

char	*file_error_handling2(t_shell *shell, int i, char *path_env)
{
	char	*buffer;

	buffer = NULL;
	if (shell->command[i].path)
	{
		buffer = malloc(ft_strlen(shell->command[i].path) + 46);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer, "minishell: %s: No such file or directory\n",
			shell->command[i].path);
	}
	else if (!shell->command[i].path && path_env)
	{
		buffer = malloc(ft_strlen(shell->command[i].cmd_name) + 46);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer, "%s: command not found\n",
			shell->command[i].cmd_name);
	}
	return (buffer);
}
