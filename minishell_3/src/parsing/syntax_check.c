/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:46:37 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 14:33:31 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	check_syntax(t_shell *shell, t_command *command, t_token *token)//5
{
	int		i;

	i = 0;
	(void)command;
	(void)shell;
	while (token[i].type != TOKEN_END)
	{
		if (check_syn_sim_one(shell, token, i))
			return (1);
		if (check_syn_sim_two(shell, token, i))
			return (1);
		i++;
	}
	check_ambig_redir(shell, command);
	return (0);
}

bool	check_syn_sim_one(t_shell *shell, t_token *token, int i)
{
	char	buffer[100];

	if (is_redir(token[i]) && is_redir(token[i + 1]))
	{
		my_sprintf(buffer, "bash: syntax error near unexpected token `%s'\n",
			token[i + 1].value);
		write(2, buffer, ft_strlen(buffer));
		shell->exit_status = 2;
		return (true);
	}
	if ((is_redir(token[i]) && token[i + 1].type == TOKEN_PIPE)
		|| (token[i].type == TOKEN_PIPE && token[i + 1].type == TOKEN_PIPE))
	{
		ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
		shell->exit_status = 2;
		return (true);
	}
	return (false);
}

bool	check_syn_sim_two(t_shell *shell, t_token *token, int i)
{
	if (last_token_pipe(token))
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		shell->exit_status = 2;
		return (true);
	}
	if (is_redir(token[i]) && token[i + 1].type == TOKEN_END)
	{
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
		shell->exit_status = 2;
		return (true);
	}
	return (false);
}

void	check_ambig_redir(t_shell *shell, t_command *command)
{
	int		i;
	int		j;
	char	*buf;

	i = -1;
	while (!command[++i].end_of_cmd)
	{
		j = -1;
		while (command[i].redirections
			&& command[i].redirections[++j].type != TOKEN_DEFAULT)
		{
			if (command[i].redirections[j].amb_redir && !command[i].p_err_msg)
			{
				buf = malloc(ft_strlen(command[i].redirections[j].file) + 50);
				if (!buf)
					free_after_malloc_fail(shell, -1, 3);
				my_sprintf(buf, "minishell: %s: ambiguous redirect\n",
					command[i].redirections[j].file);
				write(2, buf, ft_strlen(buf));
				free(buf);
				command[i].p_err_msg = true;
				break ;
			}
		}
	}
}

bool	last_token_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].type != TOKEN_END)
	{
		if (token[i + 1].type == TOKEN_END)
		{
			if (token[i].type == TOKEN_PIPE)
				return (true);
		}
		i++;
	}
	return (false);
}
