/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:16:35 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/02 14:20:04 by aismaili         ###   ########.fr       */
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
		printf("***************cmd num/index: %i	***************\n", i);
		printf("cmd_name:	%s\n", command[i].cmd_name);
		j = -1;
		printf("ARGS:\n");
		while (command[i].args[++j])
			printf("args[%i]:	%s\n", j, command[i].args[j]);
		j = -1;
		printf("REDIR:\n");
		while (command[i].redirections[++j].file)
			printf("redir[%i]:	%s\n", j, command[i].redirections[j].file);
		printf("********************next cmd********************\n");
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