/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:52:14 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 14:44:49 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

volatile sig_atomic_t	g_exit;

void	setup_minishell(t_shell *shell, char *envp[])
{
	init_all_shell(shell);
	shell->exit_status = 0;
	copy_env(envp, shell);
	sort_export(shell, envp);
	init_dir(shell);
}

void	check_argv(int ac, char *av[])
{
	char	*buffer;

	if (ac != 1)
	{
		buffer = malloc(ft_strlen(av[1]) + 60);
		if (!buffer)
		{
			perror("malloc fail");
			exit(1);
		}
		my_sprintf(buffer, "minishell: %s: No such file or directory\n", av[1]);
		write(2, buffer, ft_strlen(buffer));
		free(buffer);
		exit(127);
	}
}

int	main(int ac, char *av[], char *envp[])
{
	t_shell	shell;
	char	*input;
	int		p_status;

	check_argv(ac, av);
	setup_minishell(&shell, envp);
	while (1)
	{
		p_do_signal();
		input = readline("minishell $ ");
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		init_all_shell(&shell);
		if (check_input(&shell, input) == 1)
			continue ;
		p_status = parsing(&shell, input);
		if (p_status == 1)
			return (1);
		if (p_status == 2)
			continue ;
		begin_execution(&shell, shell.command);
		prep_next_cmd(&shell);
	}
	return (free(input), free_before_exit(&shell), 0);
}

int	check_input(t_shell *shell, char *input)
{
	if (!input)
	{
		free(input);
		write(1, "exit\n", 6);
		free_str_array(shell->env);
		free_str_array(shell->export);
		free(shell->old_dir);
		free(shell->current_dir);
		exit(shell->last_exit_status);
	}
	if (*input == 0)
	{
		free(input);
		return (1);
	}
	if (*input)
		add_history(input);
	return (0);
}

int	parsing(t_shell *shell, char *input)
{
	shell->splited = ft_split_bash(input, " \t");
	if (!shell->splited)
	{
		free_str_array(shell->env);
		free(shell->old_dir);
		free(shell->current_dir);
		return (free(input), free_str_array(shell->export), 1);
	}
	if (!shell->splited[0])
		return (free(shell->splited), free(input), 2);
	free(input);
	input = NULL;
	shell->syntax_check = token_simple(shell->splited, shell);
	if (shell->syntax_check)
		return (free_after_syntax_error(shell, 1), 2);
	expander(shell, shell->token);
	g_exit = 0;
	token_after_expansion(shell, shell->token);
	quote_removal(shell, shell->n_token);
	shell->syntax_check = token_adv(shell, shell->n_token);
	if (shell->syntax_check)
		return (free_after_syntax_error(shell, 2), 2);
	prep_exec(shell, shell->command);
	return (0);
}
