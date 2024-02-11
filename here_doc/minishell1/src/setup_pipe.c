/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:15:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/09 16:37:41 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	setup_pipe(t_shell *shell, t_command *command)
{
	int		i;
	int		j;
	int		pfd[shell->num_pipes * 2];
	int		pid;
	char	*buffer;

	i = 0;
	while (i < shell->num_pipes * 2)
	{
		if (pipe(pfd + i) == -1)
			perror("pipe fail");
		i = i + 2;
	}
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		pid = fork();
		if (pid == -1)
			perror("fork fail");
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
					perror("dup2 at redir_in");
				close(command[i].last_in.i_o_fd);
			}
			else if (i > 0)//not first command
			{
				close(pfd[((i - 1) * 2) + 1]);
				dup2(pfd[(i - 1) * 2], STDIN_FILENO);
			}
			if (command[i].last_out.file)
			{
				/* if (command[i].last_out.i_o_fd >= 0)
					printf("File descriptor before dup2: %d\n", command[i].last_out.i_o_fd);
				else
					perror("Invalid file descriptor before dup2"); */
				if (command[i].no_file == true || command[i].p_err_msg == true)
					exit (1);
				//printf("inside if (%s)\n", command[i].last_out.file);
				if (dup2(command[i].last_out.i_o_fd, STDOUT_FILENO) < 0)
					perror("dup2 at redir_out");
				close(command[i].last_out.i_o_fd);
			}
			else if (i < shell->num_pipes)//not last command
			{
				close(pfd[i * 2]);
				dup2(pfd[i * 2 + 1], STDOUT_FILENO);
			}
			j = 0;
			while (j < shell->num_pipes * 2)
				close(pfd[j++]);
			execve(command[i].path, command[i].cmd_args, shell->env);
			buffer = malloc(ft_strlen(command[i].cmd_name) + 40);
			my_sprintf(buffer, "minishell: %s: command not found\n", command[i].cmd_name);//print once for each command
			write(2, buffer, ft_strlen(buffer));
			exit(1);
		}
	}
	i = -1;
	while (++i < shell->num_pipes * 2)
		close(pfd[i]);
	i = -1;
	while (++i < shell->num_pipes + 1)
		wait(NULL);
}

/* void setup_pipe(t_shell *shell, t_command *command) {
    int i, j, pid;
    int pfd[shell->num_pipes * 2]; // Pipe file descriptors

    // Create pipes
    for (i = 0; i < shell->num_pipes * 2; i += 2) {
        if (pipe(pfd + i) == -1)
            perror("pipe fail");
    }

    for (i = 0; i < shell->num_pipes + 1; i++) {
        pid = fork();
        if (pid == -1)
            perror("fork fail");
        else if (pid == 0) { // Child process
            // Handle input redirection for any command
            if (command[i].infile) {
                int inFileDesc = open(command[i].infile, O_RDONLY);
                if (inFileDesc < 0) {
                    perror("open infile");
                    exit(1);
                }
                dup2(inFileDesc, STDIN_FILENO);
                close(inFileDesc);
            } else if (i > 0) { // If no infile, and not the first command, read from the previous pipe
                dup2(pfd[(i - 1) * 2], STDIN_FILENO);
            }

            // Handle output redirection for any command
            if (command[i].outfile) {
                int outFileDesc = open(command[i].outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
                if (outFileDesc < 0) {
                    perror("open outfile");
                    exit(1);
                }
                dup2(outFileDesc, STDOUT_FILENO);
                close(outFileDesc);
            } else if (i < shell->num_pipes) { // If no outfile, and not the last command, write to the next pipe
                dup2(pfd[i * 2 + 1], STDOUT_FILENO);
            }

            // Close all pipe fds in the child
            for (j = 0; j < shell->num_pipes * 2; j++)
                close(pfd[j]);

            execve(command[i].path, command[i].cmd_args, shell->env);

            // Command not found or execve failed
            fprintf(stderr, "minishell: %s: command not found\n", command[i].cmd_name);
            exit(1);
        }
    }

    // Parent process closes all pipe fds
    for (i = 0; i < shell->num_pipes * 2; i++)
        close(pfd[i]);

    // Parent waits for all child processes
    for (i = 0; i < shell->num_pipes + 1; i++)
        wait(NULL);
} */















/* void	setup_pipe(t_shell *shell, t_command *command)
{
	int		i;
	int		j;
	int		pfd[shell->num_pipes * 2];
	int		pid;
	char	*buffer;

	i = 0;
	while (i < shell->num_pipes * 2)
	{
		if (pipe(pfd + i) == -1)
			perror("pipe fail");
		i = i + 2;
	}
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		pid = fork();
		if (pid == -1)
			perror("fork fail");
		else if (pid == 0)
		{
			if (i > 0)//not first command
			{
				close(pfd[((i - 1) * 2) + 1]);
				dup2(pfd[(i - 1) * 2], STDIN_FILENO);
			}
			if (i < shell->num_pipes)//not last command
			{
				close(pfd[i * 2]);
				dup2(pfd[i * 2 + 1], STDOUT_FILENO);
			}
			j = 0;
			while (j < shell->num_pipes * 2)
				close(pfd[j++]);
			execve(command[i].path, command[i].cmd_args, shell->env);
			buffer = malloc(ft_strlen(command[i].cmd_name) + 40);
			my_sprintf(buffer, "minishell: %s: command not found\n", command[i].cmd_name);//print once for each command
			write(2, buffer, ft_strlen(buffer));
			exit(1);
		}
	}
	i = -1;
	while (++i < shell->num_pipes * 2)
		close(pfd[i]);
	i = -1;
	while (++i < shell->num_pipes + 1)
		wait(NULL);
} */

/* void	handle_builtin(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	if (is_builtin())
	excute_built_in(shell, command);
	
} */
