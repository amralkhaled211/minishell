/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_advance3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:04:00 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/19 15:52:17 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	default_cmd_redir(t_shell *shell, t_command *command, int i,
		int num_pipes)
{
	int	j;
	int	num_redir;

	num_redir = cound_cmd_redir(shell, i) + 2;
	j = -1;
	if (i < (num_pipes + 1))
	{
		command->redirections = malloc(sizeof(t_redirection) * (num_redir));
		if (!command->redirections)
			free_after_malloc_fail(shell, i, 4);
		while (command->redirections && ++j < num_redir)
		{
			command->redirections[j].type = TOKEN_DEFAULT;
			command->redirections[j].input_fd = -1;
			command->redirections[j].output_fd = -1;
			command->redirections[j].file = NULL;
			command->redirections[j].docfl = NULL;
			command->redirections[j].amb_redir = false;
			command->redirections[j].with_quotes = false;
		}
	}
	else
		command->redirections = NULL;
}

int	cound_cmd_redir(t_shell *shell, int cmd_nr)
{
	int	num_redir;
	int	pipe_nr;
	int	i;

	num_redir = 0;
	pipe_nr = 0;
	i = 0;
	while (cmd_nr < (shell->num_pipes + 1) && cmd_nr > pipe_nr
		&& shell->n_token[i].type != TOKEN_END)
	{
		if (shell->n_token[i].type == TOKEN_PIPE)
			pipe_nr++;
		i++;
	}
	while (shell->n_token[i].type != TOKEN_END)
	{
		if (shell->n_token[i].type == TOKEN_PIPE)
			break ;
		if (is_redir(shell->n_token[i]))
			num_redir++;
		i++;
	}
	return (num_redir);
}

void	default_cmd_args(t_shell *shell, t_command *cmd, int i, int num_pipes)
{
	int	j;

	j = -1;
	if (i < (num_pipes + 1))
	{
		cmd->args = malloc(sizeof(char *) * (shell->num_tokens + 1));
		if (!cmd->args)
			free_after_malloc_fail(shell, i, 4);
		cmd->expanded_args = malloc(sizeof(bool) * (shell->num_tokens + 1));
		if (!cmd->expanded_args)
			free_after_malloc_fail(shell, -1, 4);
		while (cmd->args && ++j < shell->num_tokens)
		{
			cmd->args[j] = NULL;
			cmd->expanded_args[j] = false;
		}
	}
	else
		cmd->args = NULL;
}

void	default_cmd_flags(t_command *command)
{
	command->no_file = false;
	command->p_err_msg = false;
	command->end_of_cmd = false;
	command->detected_amb = false;
	command->is_built_in = false;
	command->is_path = false;
	command->expanded_cmd = false;
}

void	default_last_io(t_command *command)
{
	command->last_in.file = NULL;
	command->last_in.i_o_fd = -1;
	command->last_out.file = NULL;
	command->last_out.i_o_fd = -1;
}
