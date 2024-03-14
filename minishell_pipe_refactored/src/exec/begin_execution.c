/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:15:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/14 18:12:57 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"
#include <stdlib.h>

static void	close_pfd(int **pfd)
{
	if (pfd[0][0] != -1)
		close(pfd[0][0]);
	if (pfd[0][1] != -1)
		close(pfd[0][1]);
	if (pfd[1][0] != -1)
		close(pfd[1][0]);
	if (pfd[1][1] != -1)
		close(pfd[1][1]);
}

static pid_t	*allocate_exec(t_shell *shell, pid_t *child_pid)
{
	child_pid = malloc(sizeof(pid_t) * (shell->num_pipes + 1));
	if (!child_pid)
	{
		free_after_malloc_fail(shell, -1, 5);
		return (NULL);
	}
	return (child_pid);
}

void	begin_execution(t_shell *shell, t_command *command)
{
	int		**pfd;
	pid_t	*child_pid;

	if (single_built_in(shell, command))
		return ;
	pfd = malloc(sizeof(int *) * 2);
	if (!pfd)
		free_after_malloc_fail(shell, -1, 5);
	pfd[0] = malloc(sizeof(int) * 2);
	if (!pfd[0])
	{
		free(pfd);
		free_after_malloc_fail(shell, -1, 5);
	}
	pfd[1] = malloc(sizeof(int) * 2);
	if (!pfd[1])
	{
		free(pfd[0]);
		free(pfd);
		free_after_malloc_fail(shell, -1, 5);
	}
	pfd[0][0] = -1;
	pfd[0][1] = -1;
	pfd[1][0] = -1;
	pfd[1][1] = -1;
	child_pid = NULL;
	child_pid = allocate_exec(shell, child_pid);
	multi_cmd(shell, child_pid, pfd);
}

void	handle_execution(t_shell *shell, pid_t *child_pid, int **pfd, int i)
{
	int	f;

	f = 0;
	c_handle_backslash();
	c_do_signal();
	if (i % 2 != 0)
		f = 1;
	if (pipe(pfd[f]) == -1)
		free_after_malloc_fail(shell, -1, 5);
	signal(SIGPIPE, SIG_IGN);
	child_pid[i] = fork();
	if (child_pid[i] == -1)
	{
		clean_exec_part(pfd, child_pid, true);
		free_after_malloc_fail(shell, -1, 5);
	}
	else if (child_pid[i] == 0)
	{
		main_exec_child(shell, child_pid, pfd, i);	
	}
	close_after_fork(shell, pfd, i);
}

void	multi_cmd(t_shell *shell, pid_t *child_pid, int **pfd)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		handle_execution(shell, child_pid, pfd, i);
	}
	close_pfd(pfd);
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		if (waitpid(child_pid[i], &status, 0) > 0)
			shell->exit_status = WEXITSTATUS(status);
	}
	free(pfd[0]);
	free(pfd[1]);
	free(pfd);
	free(child_pid);
}
