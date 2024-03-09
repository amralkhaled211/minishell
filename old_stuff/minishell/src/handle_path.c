/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:58:25 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/11 14:27:18 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

bool	is_path(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	//printf("str: %s\n", str);
	if (str[i] == '.' && str[i + 1] == '/')
		return (true);
	if (str[i] == '/')
		return (true);
	return (false);
}

void	handle_path(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	while (!command[i].end_of_cmd)
	{
		//printf("command[%i].cmd_name: %s\n", i, command[i].cmd_name);
		if (is_path(command[i].cmd_name))
			update_cmd_name(shell, &command[i]);
		else
			set_path(shell, &command[i]);
		i++;
	}
}

void	update_cmd_name(t_shell *shell, t_command *command)
{
	char	*temp;

	temp = extract_cmd_name(shell, command->cmd_name);//protected inside of the function
	command->path = command->cmd_name;//set path
	if (access(command->path, X_OK) != 0)
		perror("NO access to PATH");
	command->cmd_name = temp;//updated cmd_name
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
		free_after_malloc_fail(shell, 0, 4);
	while (str[len])
		temp[i++] = str[len++];
	temp[i] = 0;
	return (temp);
}

void	set_path(t_shell *shell, t_command *command)
{
	char	*path_env;
	char	**s_path;
	char	*tmp_cmd_name;
	int		i;

	(void)shell;
	path_env = get_env_var_value(shell->env, "PATH");
	if (!path_env && errno != 0)
		free_after_malloc_fail(shell, 0, 4);
	s_path = ft_split(path_env, ':');
	if (!s_path)
		free_after_malloc_fail(shell, 0, 4);
	tmp_cmd_name = add_slash(command->cmd_name);
	if (!tmp_cmd_name)
		free_after_malloc_fail(shell, 0, 4);
	i = 0;
	while (s_path[i])
	{
		command->path = ft_strjoin(s_path[i], tmp_cmd_name);
		if (!command->path)
		{
			free(tmp_cmd_name);
			free_after_malloc_fail(shell, 0, 4);
		}
		if (access(command->path, X_OK) == 0)
			break ;
		else
		{
			free(command->path);
			command->path = NULL;
		}
		i++;
	}
	free_str_array(s_path);
	free(tmp_cmd_name);
}

char	*add_slash(char *str)
{
	char	*temp;

	temp = malloc(ft_strlen(str) + 2);//one for the slash
	if (!temp)
		return (NULL);
	temp[0] = '/';
	ft_memcpy(temp + 1, str, ft_strlen(str));
	temp[ft_strlen(str) + 1] = 0;
	return (temp);
}

/*

/nfs/homes/aismaili/.local/funcheck/host:/nfs/homes/aismaili/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

*/
