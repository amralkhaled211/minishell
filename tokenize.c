/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:11:45 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/07 20:47:13 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../../libft/libft.h"

# define MAX_ARGS	128		// Maximum number of arguments
# define MAX_CMD	128
# define MAX_TOKENS	128

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_HEREDOC,		// <<
	TOKEN_APPEND,		// >>
	TOKEN_DOLLAR,
	TOKEN_END			// End of input, value NULL
}	e_types;

typedef struct
{
	e_types	type;
	char	*value;
}	t_token;

typedef struct s_redirection
{
	e_types	type;		// REDIRECT_IN, REDIRECT_OUT, REDIRECT_APPEND, or REDIRECT_HEREDOC
	char	*file;		// Filename for redirection, or delimiter for here-document
}	t_redirection;

typedef struct s_command
{
	char			*cmd_name;			// first input and each after a pipe
	char			*args[MAX_ARGS];	// Arguments array
	t_redirection	*redirections;		// Array of redirections
	bool			pipe_send;			//Pipes
	bool			pipe_recieve;
	int				num_args;			// Number of arguments
	int				num_redirections;	// Number of redirections
}   t_command;

typedef struct s_shell
{
	t_command	command[MAX_CMD];	//second after tokens, use tokens to create the commands, and use them to create an AST, if necessary
	t_token		token[MAX_TOKENS];	// first fill tokens, get num_of_tokens
	int			num_of_commands;	//first token is a cmd and each after a Pipe, also
}	t_shell;

typedef struct s_ast_node
{
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

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
	else if (ft_strncmp(keyword, ">>", ft_strlen(keyword)))//append: do not delete exissting content in outfile, but add to it
		return (assign_type(keyword, token, TOKEN_APPEND), true);
	else if (ft_strncmp(keyword, "<<", ft_strlen(keyword)))//heredoc: a delimiter will follow directly without any space in between
		return (assign_type(keyword, token, TOKEN_HEREDOC), true);
	return (false);
}

char	*handle_dollar_sign(char *keyword, char *var)
{
	int	i = 0;
	int	j = 0;

	if (keyword[i++] == '$')
	{
		while (keyword[i])
		{
			if (keyword[i] == '{')
			{
				while (keyword[i] != '}')
					var[j++] = keyword[i++];
			}
			else
				while (keyword[i])
					var[j++] = keyword[i++];
			return (var);
		}
		return (NULL);
	}
	return (NULL);
}

e_types	handle_args(char *keyword, t_token *token)
{
	int	i = 0;
	char	*var;

	while (keyword[i])
	{
		var = handle_dollar_sign(keyword + i, var); //malloc for VAR without $
		if (var)
			assign_type(keyword + i, token, TOKEN_DOLLAR);
		if (i != 0)//means there is some string before
		

	}
}


bool	identify_type_two(char *keyword, t_token *token)//not by themselves, e.g. $, or " and ', looking for ARGS
{
	//these are special cases, that can be found at beginning, end or in the middle of tokens
	//if (ft_strncmp(keyword, "$")) // diff check for $, single and double quote
	//if keyword[0] == '$' we are dealing with a Variable
	return (assign_type(keyword, token, handle_args(keyword, token)), true);
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

	//assuming correct input; otherwise should be handled before: quotation cases, any other type, best a function to handle first splited;	
	assing_type(input[i], &shell->token[i], TOKEN_COMMAND);//first input is a cmd, if correct input; test cases: first not a cmd/wrong input
	if (shell->token[i - 1].type == TOKEN_PIPE)//check for previous type, if PIPE, this must be a cmd_name
		assing_type(input[i], &shell->token[i], TOKEN_COMMAND);//first input is a cmd, if correct input; test cases: first not a cmd/wrong input
	while (input[++i])
	{
		if (identify_type_one(input[i], &shell->token[i]))
			continue;
		identify_type_two(input[i], &shell->token[i]);
	}
}

void	test_spliting(char **splited)
{
	int i = 0;
	while (splited[i])
	{
		printf("%i: %s\n", i+1, splited[i]);
		i++;
	}
}

int	main()
{
	t_shell		shell;

	char *input = readline("parseshell $ ");
	char **splited = ft_split(input, ' ');//modify for more than just one char;
	//test_spliting(splited);
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
