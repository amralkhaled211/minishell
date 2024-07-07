/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:14:05 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:23:08 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	free_after_syntax_error(t_shell *shell, int stage)
{
	if (stage == 1)
	{
		free_str_array(shell->splited);
		free_token_array(shell->token);
	}
	else if (stage == 2)
	{
		free_str_array(shell->splited);
		free_token_array(shell->token);
		free_token_array(shell->n_token);
		free_cmd_table(shell, shell->command, -1);
	}
}

void	prep_next_cmd(t_shell *shell)
{
	free_after_syntax_error(shell, 2);
}

void	free_str_array(char **array)
{
	int	i;

	i = -1;
	if (array == NULL)
		return ;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
}
