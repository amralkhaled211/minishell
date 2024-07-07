/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:38:08 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:30:30 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

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
