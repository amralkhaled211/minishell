/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 21:15:02 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 21:16:08 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	filename_arg_required(t_shell *shell, int i)
{
	if (!ft_strcmp(shell->command[i].cmd_name, "."))
	{
		shell->exit_status = 2;
		write(2, "minishell: .: filename argument required\n", 42);
		write(2, ".: usage: . filename [arguments]\n", 34);
		return (true);
	}
	return (false);
}

char	*help_error_handling(t_shell *shell, int **pfd, int i)
{
	char	*path_env;

	errno = 0;
	if (filename_arg_required(shell, i))
		free_before_exit(shell);
	if (shell->command[i].cmd_name && shell->command[i].is_a_dir == 2)
		is_not_a_dir(shell, pfd, i);
	path_env = get_env_var_value(shell->env, "PATH");
	if (!path_env && errno != 0)
		free_after_malloc_fail(shell, 0, 5);
	if (!shell->command[i].path && shell->command[i].cmd_name[0] == 0
		&& !shell->command[i].q_removed)
	{
		shell->exit_status = 0;
		free_before_exit(shell);
	}
	return (path_env);
}

void	file_error_handling(t_shell *shell, int **pfd, int i)
{
	char	*buffer;
	char	*path_env;

	buffer = NULL;
	clean_exec_part(pfd, NULL, true);
	path_env = help_error_handling(shell, pfd, i);
	if (!path_env && !shell->command[i].path)
	{
		buffer = malloc(ft_strlen(shell->command[i].path) + 46);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer, "minishell: %s: No such file or directory\n",
			shell->command[i].cmd_name);
	}
	else
		buffer = file_error_handling2(shell, i, path_env);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 127;
	free_before_exit(shell);
}
