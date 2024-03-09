/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:18:35 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/01 20:08:43 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>



int	main(int ac, char *av[])
{
	//reading input
	char	**split;
	char	*input;
	int		status;

	status = 1;
	while (status)
	{
		input = readline("minishell $> ");
		if (!input)
			continue ;
		//parsing the input
		//tokenizing based on spaces and other special characters
		//custom tokenizer
		split = ft_split();

		//execution
	}
	return (0);
	
}



/*
	what is tokenizing? basically splitting to multiple strings, getting rid of the spaces
	we can use split for that!
	
	command with an argument
		ls -l
	command with a Path
		cat /home/user/document.txt
	command with redirection
		grep "search term" file.txt > results.txt
	cammand with Pipe
		ps aux | grep apache
	command with environment variable expansion
		echo $HOME
	command with Quotes
		echo "Hello World"
	command with combined redirection and piping
		cat file.txt | sort | uniq > unique_sorted.txt
	

	distinguish between built-in cmd and external cmd
	// Pseudocode
	if (is_builtin_command(command)) {
		execute_builtin(command, arguments);
	} else {
		execute_external_command(command, arguments);
	}


	bool	is_builtin_command()
	{
		
	}

	the right order of precedence (Vorrang) and execution flow
		General Rule
		1. Follow the logical flow of the command line as written by the user.
		2. No command is inherently prioritized over another unless dictated by 
		the control operators (|, &&, ||) or their contextual dependency.
		pipes
			command1 | command2 | command3
		logical operators
			command1 && command2
			coammnd1 || command2
		command grouping
			(command1; command2)
		redirections
			Handle input/output redirections (<, >, >>, <<) as part of 
			the command they are associated with.
			Redirections should be set up before the command execution.
		
		
		



*/
