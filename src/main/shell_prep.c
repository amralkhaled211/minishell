/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:12:18 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 14:44:26 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	init_all_shell(t_shell *shell)
{
	if (g_exit)
		shell->exit_status = g_exit;
	shell->last_exit_status = shell->exit_status;
	shell->command = NULL;
	shell->token = NULL;
	shell->num_tokens = 0;
	init_flags(&shell->flags);
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
	shell->syntax_check = 0;
}

void	init_flags(t_flags *flags)
{
	flags->cmd_flag = false;
	flags->found_in = false;
	flags->found_out = false;
}

static void	increment_shlvl(t_shell *shell, int i)
{
	int		d;
	char	*num;

	d = ft_atoi(&shell->env[i][6]) + 1;
	free(shell->env[i]);
	num = ft_itoa(d);
	if (!num)
		free_env_fail(shell, i - 1);
	shell->env[i] = ft_strjoin("SHLVL=", num);
	free(num);
	if (!shell->env[i])
		free_env_fail(shell, i);
}

void	copy_env(char **envp, t_shell *shell)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		free_env_fail(shell, -1);
	i = -1;
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env)
			free_env_fail(shell, i);
		if (ft_strncmp(shell->env[i], "SHLVL", 5) == 0)
			increment_shlvl(shell, i);
	}
	shell->env[i] = NULL;
}

void	prep_exec(t_shell *shell, t_command *command)
{
	(void)command;
	identify_built_ins(shell, shell->command);
	setup_redir(shell, shell->command);
	handle_path(shell, shell->command);
	create_args(shell, shell->command);
}
