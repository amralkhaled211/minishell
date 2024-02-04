/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:03:26 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/04 11:26:47 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

/*		FREE AT SYNTAX ERROR / BEFORE NEXT COMMAND		*/

void	free_str_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_token_array(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].type != TOKEN_END)
		free(token[i++].value);
}

void	free_cmd_table(t_shell *shell, t_command *command)
{
	int	i;
	int	j;

	i = -1;
	(void)shell;
	while (!command[++i].end_of_cmd)
	{
		if (command[i].cmd_name)
			free(command[i].cmd_name);
		j = -1;
		while (command[i].args[++j] && j < MAX_ARGS)
			free(command[i].args[j]);
		j = -1;
		while (command[i].redirections[++j].file && j < MAX_REDIR)
			free(command[i].redirections[j].file);
	}
	free(command);
}

void	free_after_syntax_error(t_shell *shell, int stage)//no exit here
{
	if (stage == 1)
	{
		free_str_array(shell->splited);//splited array
		free_token_array(shell->token);//token array
	}
	else if (stage == 2)
	{
		free_str_array(shell->splited);//splited array
		free_token_array(shell->token);//token array
		free_cmd_table(shell, shell->command);//command struct
	}
}

void	prep_next_cmd(t_shell *shell)//free token array and command array
{
	int	i;

	i = 0;
	free_after_syntax_error(shell, 2);
	while (shell->token[i].type != TOKEN_END)//flags reset
		shell->token[i++].amb_redir = false;
}

/*	FREE AFTER MALLOC FAIL / BEFORE EXIT	*/

void	free_env_fail(t_shell *shell, int m)
{
	int	i;

	perror("malloc failed");
	if (m == -1)
		exit(1);
	i = 0;
	while (i < m)
		free(shell->env[i++]);
	exit(1);
}

void	free_split_fail(t_split *split, int a)
{
	int	i;

	i = 0;
	while (i < a)
	{
		free(split->result[i]);
		i++;
	}
	free(split->result);
}

void	free_after_malloc_fail(t_shell *shell, int f, int stage)
{
	int	i;

	i = 0;
	perror("malloc failed");
	if (stage == 1)//token_simple
	{
		//free token until malloc failed
		free_str_array(shell->env);
		while (i < f)
			free(shell->token[i++].value);
		free_str_array(shell->splited);
	}
	if (stage == 2)//expander
	{
		free_str_array(shell->env);
		//clean expander section
	}
	if (stage == 3)//token_advanced
	{
		free_str_array(shell->splited);
		free_str_array(shell->env);
		free_token_array(shell->token);//token array
		//free cmd_table until allocated
		free_cmd_table(shell, shell->command);
	}
	if (stage == 4)//remove_quotes
	{
		free_str_array(shell->splited);
		free_str_array(shell->env);
		free_token_array(shell->token);//token array
		//free cmd_table until allocated
		free_cmd_table(shell, shell->command);
		//clean quote section
		//-> nothing really to clean here, since only the cmd_table is modified/newly allocated and the old immidiatly freed, we only need to free that
	}
	exit(1);
}

void	free_before_exit(t_shell *shell)
{
		free_str_array(shell->env);
		free_token_array(shell->token);//token array
		//free cmd_table until allocated
		free_cmd_table(shell, shell->command);
}

/*
stage 1: token_simple
stage 2: expander
stage 3: token_advanced
stage 4: remove_quotes
*/

/*
	free_after_syntax_error()
	free_after_execution()
	free_at_execution_fail()
*/