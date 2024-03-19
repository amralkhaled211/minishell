/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:28:19 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 14:32:12 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	setup_redir(t_shell *shell, t_command *command)
{
	int	i;
	int	j;

	i = 0;
	while (!command[i].end_of_cmd)
	{
		j = 0;
		while (command[i].redirections
			&& command[i].redirections[j].type != TOKEN_DEFAULT)
		{
			if (redir_in_out(&command[i].redirections[j]) == 1)
				command[i].redirections[j].input_fd = get_fd(shell,
						&command[i], &command[i].redirections[j]);
			else if (redir_in_out(&command[i].redirections[j]) == 2)
				command[i].redirections[j].output_fd = get_fd(shell,
						&command[i], &command[i].redirections[j]);
			j++;
		}
		command[i].num_redirections = j;
		init_last_io(shell, &command[i], command[i].redirections);
		i++;
	}
}

void	init_last_io(t_shell *shell, t_command *command,
					t_redirection *redirec)
{
	int	i;
	int	last;

	i = 0;
	shell->flags.found_in = false;
	shell->flags.found_out = false;
	last = command[i].num_redirections - 1;
	while (last >= 0)
	{
		if (redir_in_out(&redirec[last]) == 1 && !shell->flags.found_in)
		{
			command->last_in.i_o_fd = redirec[last].input_fd;
			command->last_in.file = redirec[last].file;
			shell->flags.found_in = true;
		}
		else if (redir_in_out(&redirec[last]) == 2 && !shell->flags.found_out)
		{
			command->last_out.i_o_fd = redirec[last].output_fd;
			command->last_out.file = redirec[last].file;
			shell->flags.found_out = true;
		}
		last--;
	}
}

int	redir_in_out(t_redirection *redirec)
{
	if ((redirec->type == TOKEN_REDIRECT_IN || redirec->type == TOKEN_HEREDOC))
		return (1);
	if ((redirec->type == TOKEN_REDIRECT_OUT || redirec->type == TOKEN_APPEND))
		return (2);
	return (0);
}

int	type_redir(t_redirection *redirec)
{
	if (redirec->type == TOKEN_REDIRECT_IN)
		return (1);
	if (redirec->type == TOKEN_REDIRECT_OUT)
		return (2);
	if (redirec->type == TOKEN_APPEND)
		return (3);
	if (redirec->type == TOKEN_HEREDOC)
		return (4);
	return (0);
}
