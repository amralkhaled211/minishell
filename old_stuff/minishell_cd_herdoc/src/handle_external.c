/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_external.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:02:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/11 14:42:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	handle_external(t_shell *shell, t_command *command, int *pfd, int i)
{
	int		pid;
	int		j;
	char	*buffer;

	pid = fork();
	if (pid == -1)
		perror("fork fail");//exit later
	else if (pid == 0)
	{
		//Handle input redirection for any command
		if (command[i].last_in.file)
		{
			//if there was an invalid/non-existing file, do not execute this cmd
			if (command[i].no_file == true || command[i].p_err_msg == true)
				exit (1);
			//else
			if (dup2(command[i].last_in.i_o_fd, STDIN_FILENO) < 0)
				perror("dup2 at redir_in");//must decide, how to handle dup2 fail
			close(command[i].last_in.i_o_fd);
		}
		else if (i > 0)//not first command
		{
			dup2(pfd[(i - 1) * 2], STDIN_FILENO);
			//close(pfd[(i - 1) * 2]); // Close the read end after duplicating
			//close(pfd[(i - 1) * 2 + 1]); // Close the unused write end
		}
		if (command[i].last_out.file)
		{
		/* 	if (command[i].last_out.i_o_fd >= 0)
				printf("File descriptor (outfile) before dup2: %d\n", command[i].last_out.i_o_fd);
			else
				perror("Invalid file descriptor (outfile) before dup2"); */
			if (command[i].no_file == true || command[i].p_err_msg == true)
				exit (1);
			//printf("inside if (%s)\n", command[i].last_out.file);
			if (dup2(command[i].last_out.i_o_fd, STDOUT_FILENO) < 0)
				perror("dup2 at redir_out");
			close(command[i].last_out.i_o_fd);
		}
		else if (i < shell->num_pipes)//not last command
		{
			dup2(pfd[i * 2 + 1], STDOUT_FILENO);
			//close(pfd[i * 2]);
			//close(pfd[i * 2 + 1]); // Close the write end after duplicating
			// No need to close the read end of the next pipe here; it will be used by the next command
		}
		j = 0;
		if (is_built_in(&command[i]))
			execute_built_in(shell, &command[i]);
		while (j < shell->num_pipes * 2)
			close(pfd[j++]);
		if (!is_built_in(&command[i]))
		{
			execve(command[i].path, command[i].cmd_args, shell->env);
			buffer = malloc(ft_strlen(command[i].cmd_name) + 40);
			my_sprintf(buffer, "minishell: %s: command not found\n", command[i].cmd_name);//print once for each command
			write(2, buffer, ft_strlen(buffer));
			free(buffer);
			exit(1);
		}
		exit (1);
	}
}
