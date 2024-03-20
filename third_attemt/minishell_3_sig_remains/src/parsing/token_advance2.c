/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_advance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:57:39 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/19 16:00:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	init_command(t_shell *shell, t_command *command, int i, int *b)
{
	static int	a;
	int			status;

	status = get_cmd_name(shell, command, i, &a);
	if (status)
		return (status);
	status = get_cmd_args(shell, command, i, &a);
	if (status)
		return (status);
	status = get_cmd_redir(shell, command, i, b);
	if (status)
		return (status);
	else if (shell->n_token[i].type == TOKEN_END)
	{
		command->cmd_name = NULL;
		command->path = NULL;
		command->cmd_args = NULL;
		command->end_of_cmd = true;
	}
	return (status);
}

int	get_cmd_args(t_shell *shell, t_command *command, int i, int *a)
{
	int	found;

	found = 0;
	errno = 0;
	if (is_pos_existing(shell->n_token[i].value, i)
		&& shell->flags.cmd_flag == 1 && shell->n_token[i].type == TOKEN_WORD
		&& is_cmd_arg_file_word(&shell->n_token[i - 1]))
	{
		command->args[(*a)] = ft_strdup(shell->n_token[i].value);
		if (!command->args[(*a)] && errno != 0)
			return (2);
		shell->n_token[i].type = TOKEN_ARG;
		command->expanded_args[(*a)] = shell->n_token[i].expanded;
		(*a)++;
		found = 1;
	}
	return (found);
}

int	get_cmd_redir(t_shell *shell, t_command *command, int i, int *b)
{
	int	found;

	found = 0;
	if (i > 0 && shell->n_token[i].value
		&& shell->n_token[i].type == TOKEN_WORD
		&& is_redir(shell->n_token[i - 1]))
	{
		errno = 0;
		command->redirections[(*b)].file = ft_strdup(shell->n_token[i].value);
		if (!command->redirections[(*b)].file && errno != 0)
			return (2);
		shell->n_token[i].type = shell->n_token[i - 1].type + 1;
		command->redirections[(*b)].type = shell->n_token[i - 1].type;
		command->redirections[(*b)].amb_redir = shell->n_token[i].amb_redir;
		command->redirections[(*b)].expanded_redir = shell->n_token[i].expanded;
		(*b)++;
		found = 1;
	}
	return (found);
}

int	assign_cmd_name(t_shell *shell, t_command *command, int i, int *a)
{
	command->cmd_name = ft_strdup(shell->n_token[i].value);
	if (!command->cmd_name && errno != 0)
		return (2);
	shell->n_token[i].type = TOKEN_COMMAND;
	shell->flags.cmd_flag = 1;
	command->expanded_cmd = shell->n_token[i].expanded;
	(*a) = 0;
	return (1);
}

int	get_cmd_name(t_shell *shell, t_command *command, int i, int *a)
{
	int	found;

	found = 0;
	errno = 0;
	if (i == 0 && shell->flags.cmd_flag == 0
		&& shell->n_token[i].value && shell->n_token[i].type == TOKEN_WORD)
	{
		if (assign_cmd_name(shell, command, i, a) == 2)
			return (2);
		found = 1;
	}
	else if (is_pos_existing(shell->n_token[i].value, i)
		&& shell->flags.cmd_flag == 0 && shell->n_token[i].type == TOKEN_WORD
		&& is_file_word_pipe(&shell->n_token[i - 1]))
	{
		if (assign_cmd_name(shell, command, i, a) == 2)
			return (2);
		found = 1;
	}
	return (found);
}
