/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:08:53 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 13:10:07 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_str_array(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return ;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
}

void	free_token_array(t_token *token)
{
	int	i;
	int	j;

	i = 0;
	while (token[i].type != TOKEN_END && token[i].type != TOKEN_DEFAULT)
	{
		if (token[i].value)
			free(token[i].value);
		if (token[i].var_splited)
		{
			j = -1;
			while (token[i].var_splited[++j])
				free(token[i].var_splited[j]);
			free(token[i].var_splited);
		}
		i++;
	}
	free(token);
}

void	free_cmd_table(t_shell *shell, t_command *command, int f)
{
	int	i;

	i = 0;
	(void)shell;
	if (f < 0)
		f = shell->num_pipes + 2;
	while (i < f && !command[i].end_of_cmd && i < shell->num_pipes + 1)
	{
		if (command[i].cmd_name)
			free(command[i].cmd_name);
		free_cmd_args(command, i);
		free_cmd_redir(command, i);
		if (command[i].cmd_args)
			free(command[i].cmd_args);
		if (command[i].path != NULL)
			free(command[i].path);
		i++;
	}
	free(command);
}

void	free_cmd_args(t_command *command, int i)
{
	int	j;

	j = -1;
	if (command[i].args)
	{
		while (command[i].args[++j])
			free(command[i].args[j]);
		free (command[i].args);
		command[i].args = NULL;
	}
}

void	free_cmd_redir(t_command *command, int i)
{
	int	j;

	j = -1;
	if (command[i].redirections)
	{
		while (command[i].redirections[++j].file)
		{
			if (command[i].redirections[j].docfl)
			{
				unlink(command[i].redirections[j].docfl);
				free(command[i].redirections[j].docfl);
			}
			free(command[i].redirections[j].file);
			if (command[i].redirections[j].input_fd != -1)
				close(command[i].redirections[j].input_fd);
			if (command[i].redirections[j].output_fd != -1)
				close(command[i].redirections[j].output_fd);
		}
		free(command[i].redirections);
		command[i].redirections = NULL;
	}
}
