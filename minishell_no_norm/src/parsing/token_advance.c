/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:22:32 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 17:01:18 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	count_pipes_and_allocate(t_shell *shell, t_token *token)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (&token[i] && token[i].value)
	{
		if (token[i].type == TOKEN_PIPE)
			n++;
		i++;
	}
	shell->num_pipes = n;
	shell->command = malloc(sizeof(t_command) * (shell->num_pipes + 2));
	if (!shell->command)
		free_after_malloc_fail(shell, -1, 3);
	default_command(shell, shell->command, shell->num_pipes);
}

void	default_command(t_shell *shell, t_command *command, int num_pipes)
{
	int	i;

	i = 0;
	while (i < (num_pipes + 2))
	{
		default_cmd_flags(&command[i]);
		default_last_io(&command[i]);
		command[i].cmd_name = NULL;
		command[i].path = NULL;
		command[i].cmd_args = NULL;
		command[i].args = NULL;
		command[i].redirections = NULL;
		default_cmd_args(shell, &command[i], i, num_pipes);
		default_cmd_redir(shell, &command[i], i, num_pipes);
		i++;
	}
}

int	token_adv(t_shell *shell, t_token *token)
{
	t_index		ind;
	static int	b;

	ind.a = 0;
	ind.b = 0;
	b = 0;
	count_pipes_and_allocate(shell, token);
	shell->flags.cmd_flag = 0;
	while (token[ind.a].type != TOKEN_END)
	{
		if (init_command(shell, &shell->command[ind.b], ind.a, &b) == 2)
			free_after_malloc_fail(shell, -1, 4);
		if (token[ind.a + 1].type == TOKEN_PIPE)
		{
			ind.b++;
			shell->flags.cmd_flag = 0;
			b = 0;
		}
		ind.a++;
	}
	if (init_command(shell, &shell->command[++ind.b], ind.a, &b) == 2)
		free_after_malloc_fail(shell, -1, 4);
	return (check_syntax(shell, shell->command, token));
}
