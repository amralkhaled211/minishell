/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:28:19 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/11 21:50:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	setup_redir(t_shell *shell, t_command *command)
{
	int	i;
	int	j;

	i = 0;
	//printf("IN SETUP REDIRECTION\n");
	while (!command[i].end_of_cmd)
	{
		j = 0;
		while (command[i].redirections[j].type != TOKEN_DEFAULT)
		{
			if (command[i].redirections[j].type == TOKEN_REDIRECT_IN || command[i].redirections[j].type == TOKEN_HEREDOC)
				command[i].redirections[j].input_fd = get_fd(shell, &command[i], &command[i].redirections[j]);
			else if (command[i].redirections[j].type == TOKEN_REDIRECT_OUT || command[i].redirections[j].type == TOKEN_APPEND)
				command[i].redirections[j].output_fd = get_fd(shell, &command[i], &command[i].redirections[j]);
			j++;
		}
		command[i].num_redirections = j;
		init_last_io(shell, &command[i], command[i].redirections);
		i++;
	}
}

void	init_last_io(t_shell *shell, t_command *command, t_redirection *redirec)
{
	int	i;
	int	last;

	i = 0;
	shell->flags.found_in = false;
	shell->flags.found_out = false;	
	last = command[i].num_redirections - 1;
	while (last >= 0)
	{
		if (redirec[last].type == TOKEN_REDIRECT_IN && !shell->flags.found_in)
		{
			command->last_in.i_o_fd = redirec[last].input_fd;
			command->last_in.file = redirec[last].file;
			shell->flags.found_in = true;
		}
		else if ((redirec[last].type == TOKEN_REDIRECT_OUT || redirec[last].type == TOKEN_APPEND)
				&& !shell->flags.found_out)
		{
			command->last_out.i_o_fd = redirec[last].output_fd;
			command->last_out.file = redirec[last].file;
			shell->flags.found_out = true;
		}
		last--;
	}
	/* if (command[i].last_out.i_o_fd >= 0)
		printf("File descriptor before dup2: %d\n", command[i].last_out.i_o_fd);
	else
		perror("Invalid file descriptor before dup2"); */
}

int	get_fd(t_shell *shell, t_command *command, t_redirection *redirec)
{
	int		fd;
	char	buffer[ft_strlen(redirec->file) + 50];

	fd = -1;
	(void)shell;
	(void)command;
	if (redirec->type == TOKEN_REDIRECT_IN)
	{
		fd = open(redirec->file, O_RDONLY);
		if (fd == -1)
		{
			if (!command->p_err_msg)
			{
				my_sprintf(buffer, "minishell: %s: No such file or directory\n", redirec->file);
				write(2, buffer, ft_strlen(buffer));
				command->no_file = true;
				command->p_err_msg = true;
			}
			return (fd);
		}
	}
	else if (redirec->type == TOKEN_HEREDOC)
	{
		redirec->file  = get_heredoc_name();
		if (open_heredoc(shell, redirec) == 1)
			  fd = open(redirec->file, O_RDONLY);
		else
			fd = -1;
	}
	else if (redirec->type == TOKEN_REDIRECT_OUT)
	{
		fd = open(redirec->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | 0644);
		if (fd == -1)
			return (fd);
	}
	else if (redirec->type == TOKEN_APPEND)
	{
		fd = open(redirec->file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | 0644);
		if (fd == -1)
			return (fd);
	}
	return (fd);
}
