/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:59:18 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 18:41:54 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	with_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (true);
	}
	return (false);
}

void	create_args(t_shell *shell, t_command *command)
{
	int	i;

	i = 0;
	while (!command[i].end_of_cmd)
	{
		command[i].cmd_args = join_cmd_args(shell, &command[i],
				get_size_str_array(command[i].args));
		i++;
	}
}

char	**join_cmd_args(t_shell *shell, t_command *command, int n)
{
	char	**result;
	int		i;
	int		j;

	(void)n;
	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (n + 2));
	if (!result)
	{
		free_after_malloc_fail(shell, -1, 5);
		return (NULL);
	}
	result[i] = command->cmd_name;
	i++;
	while (command->args && command->args[j])
		result[i++] = command->args[j++];
	result[i] = 0;
	return (result);
}

int	get_size_str_array(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}
