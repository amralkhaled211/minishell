/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:11:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/16 17:08:55 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "../../libft/libft.h"
#include "microshell.h"



/*
		IDENTIFY ARGS
		if after cmd no pipe, it is an arg, if again not a pipe, it is an arg
		if the next is a redir a file name must follow
		if the next is $VAR, then it is an arg
		quotes are tricky:
			"ls" " -l" : ls: cannot access ' -l': No such file or directory
		random cmd: microshell $ "asldfj"
					ex: No such file or directory
					original:
					asldfj: command not found
*/

/*
		ls -l | wc -l > outfile.txt
		first command:
			ls args: -l
		pipe indicating end of cmd and beginning of next cmd
		second command
			wc args: -l
				output redir to outfile.txt
*/

void	assing_type(char *keyword, t_token *token, e_types type)
{
	token->type = type;
	token->value = ft_strdup(keyword);
}

bool	identify_type_one(char *keyword, t_token *token)//Pipes and Redirections
{
	int	i = 0;

	if (ft_strncmp(keyword, "|", ft_strlen(keyword)))//end of cmd / begin of new cmd
		return (assign_type(keyword, token, TOKEN_PIPE), true);
	else if (ft_strncmp(keyword, ">", ft_strlen(keyword)))//outfile: output will be redirected to the following file; delete existing content in file/overwrite it
		return (assign_type(keyword, token, TOKEN_REDIRECT_OUT), true);
	else if (ft_strncmp(keyword, "<", ft_strlen(keyword)))//infile: input will be read from the following file
		return (assign_type(keyword, token, TOKEN_REDIRECT_IN), true);
	else if (ft_strncmp(keyword, ">>", ft_strlen(keyword)))//append: do not delete existing content in outfile, but add to it
		return (assign_type(keyword, token, TOKEN_APPEND), true);
	else if (ft_strncmp(keyword, "<<", ft_strlen(keyword)))//heredoc: a delimiter will follow directly with or without any space in between
		return (assign_type(keyword, token, TOKEN_HEREDOC), true);
	return (false);
}

char	*handle_dollar_sign(char *keyword, t_shell *shell)
{
	int		i = 0;
	int		j = 0;
	char	var[MAX_VAR];//on stack
	char	*value;//on stack

	if (keyword[i++] == '$')
	{
		while (keyword[i])
		{
			if (keyword[i] == '{')	// with {}: ${VAR}abc without: $VARabc; must distinguish
			{
				i++;
				while (keyword[i] != '}' && keyword[i] && j < MAX_VAR - 1)
					var[j++] = keyword[i++];
				if (keyword[i] == '}')
				{
					shell->flags.dollar_c_brack = true;
					i++;
				}
			}
			else
				while (keyword[i] && j < MAX_VAR - 1)
					var[j++] = keyword[i++];
			value = getenv(var);
			if (value)
			return ();
		}
		return (NULL);
	}
	return (NULL);
}


e_types	handle_args(char *keyword, t_shell *shell)
{
	int		i = 0;
	int		j = 0;
	char	*arg;

	while (keyword[i])
	{
		arg = handle_dollar_sign(keyword + i, shell); //malloc for VAR without $
		if (arg)

		arg[j++] = keyword[i++];

	}
	return (TOKEN_ARG);
}

bool	identify_type_two(char *keyword, int i, t_shell *shell)
{
	//these are special cases, that can be found at beginning, end or in the middle of tokens
	//if keyword[0] == '$' we are dealing with a Variable
	return (assign_type(keyword, shell->token[i], handle_args(keyword, shell)), true);
}

/*
		$: can be alone as an ARG for echo, else it is used for VARIABLES
		Quotes: unpredictable, can stand alone, be at beg ,middle or end of an ARG
		ls -l " |" wc -l > ofile.txt
		 	PIPE would not get recognized and defined as an argument
*/

void	tokenize(char **input, t_shell *shell)//identify the type
{
	int	i = 0;

	check_first(shell, input);
	assing_type(input[i], &shell->token[i], TOKEN_COMMAND);
	while (input[++i])
	{
		if (identify_type_one(input[i], &shell->token[i]))
			continue;
		identify_type_two(input[i], i, shell);
		if (i >= 2 && shell->token[i - 1].type == TOKEN_PIPE)//check for previous type, if PIPE, this must be a cmd_name
			assing_type(input[i], &shell->token[i], TOKEN_COMMAND);
	}
}

void	check_first(t_shell *shell, char **input)
{
	if (identify_type_one(input[0], &shell->token[0]))
	{
		if (shell->token->type == TOKEN_PIPE)
			return ;//bash: syntax error near unexpected token `|'
		else if (shell->token->type == TOKEN_REDIRECT_IN)
		else if (shell->token->type == TOKEN_REDIRECT_OUT)
		else if (shell->token->type == TOKEN_APPEND)
		else if (shell->token->type == TOKEN_HEREDOC)
	}
	
}

int	main(void)
{
	t_shell	shell;

	char *input = readline("parseshell $ ");
	char **splited = ft_split_bash(input, " \t");
	tokenize(splited, &shell);
}

/*
		QUOTATIONS in ft_split
		cases:
			" ls" invalid; with space: ft_split: 1.(") 2.(ls"); if first splited is anything besides a command, invalid;
			ls "-l" valid; without space: split is fine with it, but we have to remove the "" before we pass to execve!!!			
*/

/*
		ls -l | wc -l > outfile.txt
		first command:
			ls args: -l
		pipe indicating end of cmd and beginning of next cmd
		second command
			wc args: -l
				output redir to outfile.txt

		Command 1: ls -l
		command: ls
		args: ["-l"]
		pipe_to: true (indicating that the output is piped to another command)
		Command 2: wc -l

		command: wc
		args: ["-l"]
		pipe_from: true (indicating that the input is coming from a piped command)
		redirect_out: outfile.txt (for the redirection > outfile.txt)
*/

/*
	quotes must be removed when passed to execve, exept, when there is a \ before the quote
	$ echo alksdf" lak\"jf"
	alksdf lak"jf

*/