/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:16:35 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/11 13:16:19 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	print_cmd_table(t_command *command)
{
	int	i;
	int	j;

	i = 0;
	while (!command[i].end_of_cmd)
	{
		printf("*****************cmd num/index: %i *******************\n", i);
		printf("cmd_name:		%s\n", command[i].cmd_name);
		j = -1;
		printf("ARGS:\n");
		while (command[i].args[++j])
			printf("args[%i]:		%s\n", j, command[i].args[j]);
		j = -1;
		printf("REDIR:\n");
		while (command[i].redirections[++j].file)
		{
			if (command[i].redirections[j].type == TOKEN_REDIRECT_IN)
			{
				printf("redir.file[%i]:		%s\n", j, command[i].redirections[j].file);
				printf("redir.in_fd[%i]:		%i\n", j, command[i].redirections[j].input_fd);
			}
			else if (command[i].redirections[j].type == TOKEN_REDIRECT_OUT)
			{
				printf("redir.file[%i]:		%s\n", j, command[i].redirections[j].file);
				printf("redir.out_fd[%i]:	%i\n", j, command[i].redirections[j].output_fd);
			}
			else if (command[i].redirections[j].type == TOKEN_APPEND)
			{
				printf("redir.file[%i]:		%s\n", j, command[i].redirections[j].file);
				printf("redir.ap_fd[%i]:		%i\n", j, command[i].redirections[j].output_fd);
			}
		}
		//printf("\n",);
		printf("******************** next cmd ********************\n");
		i++;
	}
}

void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->token[i].value)
	{
		printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
		i++;
	}
	printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
}

void	print_split_result(char **splited)
{
	int	i;

	i = 0;
	printf("PRINTING RESULT OF SPLIT:\n");
	while (splited[i])
	{
		printf("splited[%i]: %s\n", i, splited[i]);
		i++;
	}
}
