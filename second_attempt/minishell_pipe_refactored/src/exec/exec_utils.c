/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:21:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/14 13:21:41 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	identify_built_ins(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	(void)shell;
	while (!command[i].end_of_cmd)
	{
		if (is_built_in(&command[i]))
			command[i].is_built_in = true;
		i++;
	}
}

int	execute_built_in(t_shell *shell, t_command *cmd)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		res = echo(cmd->args, shell);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		res = env(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		res = export(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		res = pwd(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		res = unset(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
	{
		res = cd(shell, cmd->args);
		if (res == -2)
			free_after_malloc_fail(shell, -1, 5);
	}
	else if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
		res = ft_exit(shell, cmd->args);
	shell->exit_status = res;
	return (res);
}

/* int	execute_built_in(t_shell *shell, t_command *cmd)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		res = echo(cmd->args, shell);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		res = env(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		res = export(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		res = pwd(shell);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		res = unset(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
	{
		res = cd(shell, cmd->args);
		if (res == -2)
			free_after_malloc_fail(shell, -1, 5);
	}
	else if (ft_strncmp(cmd->cmd_name, "exit", 5) == 0)
		res = ft_exit(shell, cmd->args);
	shell->exit_status = res;
	return (res);
} */

bool	is_built_in(t_command *cmd)
{
	if (!cmd->cmd_name)
		return (false);
	if (!ft_strncmp(cmd->cmd_name, "echo", ft_strlen("echo") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "env", ft_strlen("env") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "export", ft_strlen("export") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "pwd", ft_strlen("pwd") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "unset", ft_strlen("unset") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "cd", ft_strlen("cd") + 1))
		return (true);
	else if (!ft_strncmp(cmd->cmd_name, "exit", ft_strlen("exit") + 1))
		return (true);
	return (false);
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	clean_exec_part(int **pfd, pid_t *child_pid, int flag_free)
{
	if (pfd[0][0] != -1)
		close(pfd[0][0]);
	if (pfd[0][1] != -1)
		close(pfd[0][1]);
	if (pfd[1][0] != -1)
		close(pfd[1][0]);
	if (pfd[1][1] != -1)
		close(pfd[1][1]);
	if (flag_free)
	{
		free(pfd[0]);
		free(pfd[1]);
		free(pfd);
		free(child_pid);
	}
}
