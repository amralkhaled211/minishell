/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:30:04 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 14:47:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*get_file_path(t_shell *shell, char *file)
{
	char	*file_path;
	char	*slash_file;

	slash_file = add_slash(file);
	if (!slash_file)
		return (free_after_malloc_fail(shell, -1, 5), NULL);
	file_path = ft_strjoin(shell->current_dir, slash_file);
	if (!file_path)
		return (free(slash_file), free_after_malloc_fail(shell, -1, 5), NULL);
	return (free(slash_file), file_path);
}

int	check_file_perm(t_command *command, t_redirection *redirec, char *file_path)
{
	char	*buf;

	if (!(type_redir(redirec) % 2) && !command->p_err_msg
		&& access(file_path, R_OK) == -1)
	{
		buf = malloc(ft_strlen(redirec->file) + 50);
		if (!buf)
			return (-1);
		my_sprintf(buf, "minishell: %s: Permission denied\n", redirec->file);
		write(2, buf, ft_strlen(buf));
		command->p_err_msg = true;
		free(buf);
	}
	if ((type_redir(redirec) % 2) && !command->p_err_msg
		&& access(file_path, W_OK) == -1)
	{
		buf = malloc(ft_strlen(redirec->file) + 50);
		if (!buf)
			return (-1);
		my_sprintf(buf, "minishell: %s: Permission denied\n", redirec->file);
		write(2, buf, ft_strlen(buf));
		command->p_err_msg = true;
		free(buf);
	}
	return (0);
}

int	mini_redir_msg(t_shell *shell, t_command *command,
	t_redirection *redirec)
{
	char	*buffer;
	char	*file_path;

	file_path = get_file_path(shell, redirec->file);
	if (!file_path)
		free_after_malloc_fail(shell, -1, 5);
	if (access(file_path, F_OK) == 0
		&& check_file_perm(command, redirec, file_path) == -1)
		return (free(file_path), free_after_malloc_fail(shell, -1, 5), 1);
	free(file_path);
	if (!command->p_err_msg)
	{
		buffer = malloc(ft_strlen(redirec->file) + 100);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer,
			"minishell: %s: No such file or directory\n",
			redirec->file);
		write(2, buffer, ft_strlen(buffer));
		free(buffer);
		command->no_file = true;
		command->p_err_msg = true;
	}
	return (0);
}
