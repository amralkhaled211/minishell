/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:58:25 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 18:39:58 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	handle_path(t_shell *shell, t_command *command)
{
	int	i;

	i = -1;
	while (!command[++i].end_of_cmd)
	{
		if (is_path(command[i].cmd_name))
			update_cmd_name(shell, &command[i]);
		else
		{
			if ((!ft_strcmp(command->cmd_name, "..")
					|| !ft_strcmp(command->cmd_name, ".")))
				continue ;
			set_path(shell, &command[i]);
		}
	}
}

void	update_cmd_name(t_shell *shell, t_command *command)
{
	char	*temp;

	temp = extract_cmd_name(shell, command->cmd_name);
	command->path = ft_strdup(command->cmd_name);
	if (!command->path && errno != 0)
		free_after_malloc_fail(shell, -1, 5);
	free(command->cmd_name);
	command->cmd_name = temp;
}

char	*extract_cmd_name(t_shell *shell, char *str)
{
	char	*temp;
	int		i;
	int		len;

	(void)shell;
	i = 0;
	len = ft_strlen(str) - 1;
	while (len && str[len] != '/')
		len--;
	len++;
	temp = malloc(ft_strlen(str) - len + 1);
	if (!temp)
	{
		free_after_malloc_fail(shell, 0, 4);
		return (NULL);
	}
	while (str && temp && str[len])
		temp[i++] = str[len++];
	temp[i] = 0;
	return (temp);
}

void	set_path(t_shell *shell, t_command *command)
{
	char	*path_env;
	char	**s_path;
	char	*tmp_cmd_name;

	(void)shell;
	errno = 0;
	if ((command->cmd_name && !command->cmd_name[0]))
		return ;
	path_env = get_env_var_value(shell->env, "PATH");
	if (!path_env && errno != 0)
		free_after_malloc_fail(shell, 0, 5);
	if (!path_env && errno == 0)
		path_env = shell->current_dir;
	s_path = ft_split(path_env, ':');
	if (!s_path && errno != 0)
		free_after_malloc_fail(shell, 0, 5);
	tmp_cmd_name = add_slash(command->cmd_name);
	if (!tmp_cmd_name && errno != 0)
	{
		free_str_array(s_path);
		free_after_malloc_fail(shell, 0, 5);
	}
	mini_set_path(shell, command, s_path, tmp_cmd_name);
	free_str_array(s_path);
	free(tmp_cmd_name);
}

void	mini_set_path(t_shell *shell, t_command *cmd, char **s_path, char *tcn)
{
	int	i;

	i = 0;
	while (s_path && s_path[i])
	{
		errno = 0;
		cmd->path = ft_strjoin(s_path[i], tcn);
		if (!cmd->path && errno != 0)
		{
			free_str_array(s_path);
			free(tcn);
			tcn = NULL;
			free_after_malloc_fail(shell, -1, 5);
			return ;
		}
		if (cmd->path && access(cmd->path, X_OK) == 0)
			break ;
		else
		{
			free(cmd->path);
			cmd->path = NULL;
		}
		i++;
	}
}
