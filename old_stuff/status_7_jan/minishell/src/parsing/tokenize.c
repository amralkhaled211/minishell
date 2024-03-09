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

# define MAX_ARGS 	128  // Maximum number of arguments
# define MAX_CMD  	128
# define MAX_TOKENS 128

typedef enum
{
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,		 // |
	TOKEN_REDIRECT_IN,  // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_HEREDOC,	  // <<
	TOKEN_APPEND,	   // >>
	TOKEN_END		   // End of input
}	e_types;


typedef struct
{
	e_types type;
	char* value;
}	t_token;

typedef struct s_redirection {
    char *type;    // REDIRECT_IN, REDIRECT_OUT, REDIRECT_APPEND, or REDIRECT_HEREDOC
    char *file;    // Filename for redirection, or delimiter for here-document
}   t_redirection;

typedef struct s_command
{
	char			*cmd_name;				// first input and each after a pipe
	char			*args[MAX_ARGS];	// Arguments array
	t_redirection	*redirections;		// Array of redirections
	bool			pipe_to;				//Pipes
	bool			pipe_from;
	int				num_args;			// Number of arguments
	int				num_redirections;	// Number of redirections
	
}   t_command;

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

typedef struct s_shell
{
	t_command	command[MAX_CMD];
	t_token		token[MAX_TOKENS];
	int			num_of_commands; //first token is a cmd and each after a Pipe, also
}	t_shell;

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
	token->value = keyword;
}

void	identify_type_one(char *keyword, t_token *token)//Pipes and Redirections
{
	int	i = 0;

	if (ft_strncmp(keyword, "|", ft_strlen(keyword)))//end of cmd / begin of new cmd
		assign_type(keyword, token, TOKEN_PIPE);
	else if (ft_strncmp(keyword, ">", ft_strlen(keyword)))//outfile: output will be redirected to the following file; delete existing content in file/overwrite it
		assign_type(keyword, token, TOKEN_REDIRECT_OUT);
	else if (ft_strncmp(keyword, "<", ft_strlen(keyword)))//infile: input will be read from the following file
		assign_type(keyword, token, TOKEN_REDIRECT_IN);
	else if (ft_strncmp(keyword, ">>", ft_strlen(keyword)))//append: do not delete exissting content in outfile, but add to it
		assign_type(keyword, token, TOKEN_APPEND);
	else if (ft_strncmp(keyword, "<<", ft_strlen(keyword)))//heredoc: a delimiter will follow directly without any space in between
		assign_type(keyword, token, TOKEN_HEREDOC);
}

void	identify_type_two()//not by themselves, e.g. $, " and '
{
	//these are special cases, that can be found at beginning, end or in the middle of tokens
	//else if (ft_strncmp(keyword, "$"))
	//else if (ft_strncmp(keyword, "\""))
	//else if (ft_strncmp(keyword, "\'"))
}

void	tokenize(char **input, t_shell *shell)//identify the type
{
	int	i = 0;
	//assuming correct input; otherwise should be handled before: quotation cases, any other type, best a function to handle first splited;
	assing_type(input[i], &shell->token[i], TOKEN_COMMAND);//first input is a cmd, if correct input; test cases: first not a cmd/wrong input
	while (input[++i])
	{
		identify_type_one(input[i], &shell->token[i]);
		//identify_type_two();
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
	test_spliting(splited);
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