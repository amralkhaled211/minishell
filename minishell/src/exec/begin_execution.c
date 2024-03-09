/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:15:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 18:44:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	close_pfd(int *pfd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes * 2)
	{
		if (pfd && pfd[i] != -1)
		{
			close(pfd[i]);
			pfd[i] = -1;
		}
		i++;
	}
}

static pid_t	*allocate_exec(t_shell *shell, pid_t *child_pid, int *pfd)
{
	child_pid = malloc(sizeof(pid_t) * (shell->num_pipes + 1));
	if (!child_pid)
	{
		free(pfd);
		pfd = NULL;
		free_after_malloc_fail(shell, -1, 5);
		return (NULL);
	}
	return (child_pid);
}

static void	create_pipes(t_shell *shell, pid_t *child_pid, int *pfd)
{
	int	i;

	i = 0;
	while (i < shell->num_pipes * 2)
	{
		if (pfd && pipe(pfd + i) == -1)
		{
			clean_exec_part(pfd, child_pid, shell->num_pipes);
			pfd = NULL;
			free_after_malloc_fail(shell, -1, 5);
			return ;
		}
		i = i + 2;
	}
}

void	begin_execution(t_shell *shell, t_command *command)
{
	int		*pfd;
	pid_t	*child_pid;

	child_pid = NULL;
	if (single_built_in(shell, command))
		return ;
	pfd = malloc(sizeof(int) * (shell->num_pipes * 2));
	if (!pfd)
		free_after_malloc_fail(shell, -1, 5);
	child_pid = allocate_exec(shell, child_pid, pfd);
	if (!child_pid)
	{
		pfd = NULL;
		return ;
	}
	create_pipes(shell, child_pid, pfd);
	multi_cmd(shell, child_pid, pfd);
}

void	multi_cmd(t_shell *shell, pid_t *child_pid, int *pfd)
{
	int	status;
	int	i;

	status = 0;
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		handle_execution(shell, child_pid, pfd, i);
	}
	close_pfd(pfd, shell->num_pipes);
	i = -1;
	while (++i < shell->num_pipes + 1)
	{
		if (waitpid(child_pid[i], &status, 0) > 0)
			shell->exit_status = WEXITSTATUS(status);
	}
	clean_exec_part(pfd, child_pid, shell->num_pipes);
}
