/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:23 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 16:56:53 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	remove_quotes(t_shell *shell, t_command *command)
{
	int		i;
	char	*temp;

	i = 0;
	(void)shell;
	while (!command[i].end_of_cmd)
	{
		errno = 0;
		temp = handle_quotes(shell, command[i].cmd_name);
		free(command[i].cmd_name);
		command[i].cmd_name = temp;
		rm_quotes_args(shell, &command[i]);
		rm_quotes_redir(shell, &command[i]);
		i++;
	}
}

void	rm_quotes_args(t_shell *shell, t_command *command)
{
	int		j;
	char	*temp;

	j = 0;
	while (command->args && command->args[j])
	{
		temp = handle_quotes(shell, command->args[j]);
		free(command->args[j]);
		command->args[j] = temp;
		j++;
	}
}

void	rm_quotes_redir(t_shell *shell, t_command *command)
{
	int		j;
	char	*temp;

	j = 0;
	while (command->redirections && command->redirections[j].file)
	{
		if (with_quote(command->redirections[j].file))
			command->redirections[j].with_quotes = true;
		temp = handle_quotes(shell, command->redirections[j].file);
		free(command->redirections[j].file);
		command->redirections[j].file = temp;
		j++;
	}
}

char	*handle_quotes(t_shell *shell, char *input)
{
	int		len;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = malloc(len + 1);
	if (!result)
		free_after_malloc_fail(shell, -1, 4);
	mini_handle_quote(input, result, len);
	return (result);
}

void	mini_handle_quote(char *input, char *result, int len)
{
	int		i[2];
	int		in_dquote;
	int		in_squote;

	in_squote = 0;
	in_dquote = 0;
	i[0] = 0;
	i[1] = 0;
	if (!result || !input)
		return ;
	while (i[0] < len)
	{
		if (input[i[0]] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i[0]] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else
			result[i[1]++] = input[i[0]];
		i[0]++;
	}
	result[i[1]] = '\0';
}
