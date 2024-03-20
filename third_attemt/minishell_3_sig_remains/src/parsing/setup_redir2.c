/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:38:08 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/19 20:32:26 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*get_file_path(t_shell *shell, char *file)
{
	int		i;
	char	*file_path;
	char	*slash_file;

	i = 0;
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
	char	*buffer;

	if (!(type_redir(redirec) % 2) && access(file_path, R_OK) == -1)//IN
	{
		buffer = malloc(ft_strlen(redirec->file) + 50);
		if (!buffer)
			return (free(file_path), -1);
		my_sprintf(buffer, "minishell: %s: Permission denied\n", redirec->file);
		write(2, buffer, ft_strlen(buffer));
		command->p_err_msg = true;
		free(buffer);
	}
	if ((type_redir(redirec) % 2) && access(file_path, W_OK) == -1)//OUT
	{
		buffer = malloc(ft_strlen(redirec->file) + 50);
		if (!buffer)
			return (free(file_path), -1);
		my_sprintf(buffer, "minishell: %s: Permission denied\n", redirec->file);
		write(2, buffer, ft_strlen(buffer));
		command->p_err_msg = true;
		free(buffer);
	}
	return (free(file_path), 0);
}

static void	mini_redir_msg(t_shell *shell, t_command *command,
	t_redirection *redirec)
{
	char	*buffer;
	char	*file_path;

	file_path = get_file_path(shell, redirec->file);
	if (!file_path)
		free_after_malloc_fail(shell, -1, 5);
	if (check_file_perm(command, redirec, file_path) == -1)
		free_after_malloc_fail(shell, -1, 5);
	if (!command->p_err_msg)
	{
		buffer = malloc(ft_strlen(redirec->file) + 100);
		if (!buffer)
			free_after_malloc_fail(shell, -1, 5);
		my_sprintf(buffer,
			"minishell: %s: No such file or directory[IN PARENT]\n",
			redirec->file);//in case file does not exit [INPUT] //in case file
		write(2, buffer, ft_strlen(buffer));
		free(buffer);
		command->no_file = true;
		command->p_err_msg = true;
	}
}

int	handle_redir_in(t_shell *shell, t_command *command, t_redirection *redirec)
{
	int		fd;

	(void)shell;
	fd = -1;
	if (type_redir(redirec) == 1 && !redirec->amb_redir
		&& !command->detected_amb)
	{
		fd = open(redirec->file, O_RDONLY);
		if (fd == -1)
		{
			mini_redir_msg(shell, command, redirec);
			return (fd);
		}
	}
	return (fd);
}

int	handle_here_doc(t_shell *shell, t_command *cmd, t_redirection *redirec)
{
	int	fd;

	fd = -1;
	if (type_redir(redirec) == 4 && !redirec->amb_redir && !cmd->detected_amb)
	{
		redirec->docfl = get_heredoc_name();
		if (!redirec->docfl)
			free_after_malloc_fail(shell, -1, 4);
		if (open_heredoc(shell, redirec) == 1)
		{
			fd = open(redirec->docfl, O_RDONLY);
			if (fd == -1)
				free_after_malloc_fail(shell, -1, 4);
		}
		else
		{
			fd = -1;
			cmd->no_file = true;
		}
	}
	return (fd);
}

int	handle_redir_out_append(t_shell *shell, t_command *cmd,
	t_redirection *redirec)
{
	int	fd;

	(void)shell;
	fd = -1;
	if (type_redir(redirec) == 2 && !redirec->amb_redir && !cmd->detected_amb)
	{
		fd = open(redirec->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH | 0644);
		if (fd == -1)
			return (mini_redir_msg(shell, cmd, redirec), fd);
	}
	else if (type_redir(redirec) == 3 && !redirec->amb_redir
		&& !cmd->detected_amb)
	{
		fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH | 0644);
		if (fd == -1)
			return (mini_redir_msg(shell, cmd, redirec), fd);
	}
	return (fd);
}

int	get_fd(t_shell *shell, t_command *command, t_redirection *redirec)
{
	int		fd;

	if (redirec->amb_redir)
		command->detected_amb = 1;
	fd = handle_redir_in(shell, command, redirec);
	if (fd != -1)
		return (fd);
	fd = handle_redir_out_append(shell, command, redirec);
	if (fd != -1)
		return (fd);
	fd = handle_here_doc(shell, command, redirec);
	if (fd != -1)
		return (fd);
	return (fd);
}
