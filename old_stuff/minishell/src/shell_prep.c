/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:12:18 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/10 19:27:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	init_all_shell(t_shell *shell)
{
	int	i;

	i = -1;
	shell->command = NULL;
	while (++i < MAX_TOKENS)
	{
		shell->token[i].amb_redir = false;
		shell->token[i].type = TOKEN_DEFAULT;
		shell->token[i].value = NULL;
	}
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

void	copy_env(char **envp, t_shell *shell)
{
	int		i;
	int		d;
	char	*num;

	i = 0;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * (i + 1));
	if (!shell->env)
		free_env_fail(shell, -1);//just exit, nothing to free
	i = -1;
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env)
			free_env_fail(shell, i);
		if (strncmp(shell->env[i], "SHLVL", 5) == 0)//increment the SHLVL
		{
			d = ft_atoi(&shell->env[i][6]) + 1;
			free(shell->env[i]);
			num = ft_itoa(d);
			if (!num)
				free_env_fail(shell, i - 1);// i - 1, env[i] already freed
			shell->env[i] = ft_strjoin("SHLVL=", num);
			free(num);
			if (!shell->env[i])
				free_env_fail(shell, i);//free all the allocated env and exit
		}
	}
	shell->env[i] = NULL;
}
