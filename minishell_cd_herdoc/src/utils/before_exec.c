/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:40:23 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/10 12:37:35 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	remove_quotes(t_shell *shell, t_command *command)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	(void)shell;
	while (command[i].cmd_name)
	{
		temp = handle_quotes(shell, command[i].cmd_name);
		if (!temp)
				free_after_malloc_fail(shell, 0, 4);
		free(command[i].cmd_name);
		command[i].cmd_name = temp;
		j = 0;
		while (command[i].args[j])
		{
			temp = handle_quotes(shell, command[i].args[j]);
			if (!temp)
				free_after_malloc_fail(shell, 0, 4);
			free(command[i].args[j]);
			command[i].args[j] = temp;
			j++;
		}
		j = 0;
		while (command[i].redirections[j].file)
		{
			temp = handle_quotes(shell, command[i].redirections[j].file);
			if (!temp)
				free_after_malloc_fail(shell, 0, 4);
			free(command[i].redirections[j].file);
			command[i].redirections[j].file = temp;
			j++;
		}
		i++;
	}
}

char	*handle_quotes(t_shell *shell, char *input)
{
	int		len;
	int		i[2];
	int		in_dquote;
	int		in_squote;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	in_squote = 0;
	in_dquote = 0;
	i[0] = 0;
	i[1] = 0;
	result = malloc(len + 1);
	if (!result)
		free_after_malloc_fail(shell, 0, 4);
	while (i[0] < len)
	{
		if (input[i[0]] == '\'' && !in_dquote)
			in_squote = !in_squote;// Toggle the single quote state if not inside double quotes
		else if (input[i[0]] == '\"' && !in_squote)
			in_dquote = !in_dquote;// Toggle the double quote state if not inside single quotes
		else
			result[i[1]++] = input[i[0]];// Copy other characters
		i[0]++;
	}
	result[i[1]] = '\0';
	return (result);
}

void	create_args(t_shell *shell, t_command *command)
{
	int	i;
	//int	j;

	i = 0;
	//j = 0;
	while (!command[i].end_of_cmd)
	{
		command[i].cmd_args = join_cmd_args(shell, &command[i], get_size_args(command[i].args));
		i++;
	}
}

char	**join_cmd_args(t_shell *shell, t_command *command, int n)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (n + 2));//2: including the cmd_name
	if (!result)
		free_after_malloc_fail(shell, 0, 4);
	result[i] = command->cmd_name;
	i++;
	while (command->args[j])
		result[i++] = command->args[j++];
	result[i] = 0;
	return (result);
}

int	get_size_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/*
//case: "$"HOME convert to: $HOME
		if (begin_end[0] > 0 && begin_end[1] != ft_strlen(command[i].cmd_name) - 1)
		{
		}
		//case: hello" world "bye convert to: hello world bye
		if ()
		{
			
		}
		//case: ""
		//case: "" delete
		if ()
		{
			
		}
		*/
/* void	store_quotes(char *str)
{
	t_split	zitat;
	int		i;
	char	quote;
	bool	in_quote;
	int		begin_end[2];

	begin_end[0] = 0;
	begin_end[1] = first_quote_pos(str);
	in_quote = false;
	quote = '\0';
	i = 0;
	reset_split_var(&zitat);
	while (str[i])
	{
		//case: abc "hell'o wor'ld" def "df"dkf"dsf"dsaf
		if (is_quote(str) && (!in_quote || quote == str[i]))
		{
			in_quote = !in_quote;
			if (in_quote)
			{
				quote = str[i];
				begin_end[0] = i;
			}
			else
			{
				quote = '\0';
				begin_end[1] = i;
			}
		}
		else if (!in_quote)
		{
			//save_outside();
			zitat.result[zitat.a] = ft_substr(str, begin_end[0], begin_end[1] - begin_end[0]);
			if (begin_end[0] == 0)
				i = begin_end[1] - 1;
		}
		i++;
	}
} */
/* void	remove_quotes(t_shell *shell, t_command *command, char *str)
{
	t_split	q_split;

	int		i;
	int		j;
	char	*temp;
	char	quote;
	bool	in_quote;
	int		begin_end[2];

	begin_end[0] = 0;
	begin_end[1] = first_quote_pos();
	in_quote = false;
	quote = '\0';

	i = 0;
	j = 0;
	while (!command[i].end_of_cmd)
	{
		if (with_quotes_nor(command[i].cmd_name))//command_name
		{
			temp = ft_substr(command[i].cmd_name, 1, ft_strlen(command[i].cmd_name) - 2);
			free(command[i].cmd_name);
			command[i].cmd_name = temp;
		}
		while (command[i].cmd_name[j])
		{
			//case: abc "hell'o wor'ld" def "df"dkf"dsf"dsaf
			if (is_quote(command[i].cmd_name[j]) && (!in_quote || quote == command[i].cmd_name[j]))
			{
				in_quote = !in_quote;
				if (in_quote)
				{
					quote = command[i].cmd_name[j];
					begin_end[0] = j;
				}
				else
				{
					quote = '\0';
					begin_end[1] = j;
				}
			}
			if (!in_quote)
			{
				//save_outside();
				ft_substr(str, begin_end[0], begin_end[1] - begin_end[0]);
			}
			j++;
		}
	}
} */
/* bool	with_quotes_nor(char *str)
{
	int	i;
	int	last;

	i = 0;
	last = ft_strlen(str) - 1;	
	if (str[0] == '"' && str[last] == '"')
		return (true);
	else if (str[0] == '\'' && str[last] == '\'')
		return (true);
	return (false);
} */