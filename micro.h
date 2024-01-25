#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define MAX_ARGS	128		// Maximum number of arguments
# define MAX_CMD	128
# define MAX_TOKENS	30
# define MAX_VAR	128

typedef enum en_types
{
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_REDIRECT_IN,	// <
	TOKEN_APPEND,		// >>
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF,
	TOKEN_FILE,
	TOKEN_DOLLAR,
	TOKEN_END			// End of input, value NULL
}	e_types;

typedef struct s_token
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
    int             num_redir_in;
    int             num_redir_out;
}   t_command;

typedef struct s_flags
{
	bool	dollar_c_brack;		//String can continue after c_bracket
	int		cmd_flag;
}	t_falgs;

typedef struct s_shell
{
	t_command	*command;	//second after tokens, use tokens to create the commands, and use them to create an AST, if necessary
	t_token		token[MAX_TOKENS];	// first fill tokens, get num_of_tokens
	int			num_of_commands;	//first token is a cmd and each after a Pipe, also
	t_falgs		flags;
}	t_shell;

typedef struct s_ast_node
{
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef struct s_split
{
	char	**result;
	int		a;
	int		i;
	int		num_words;
	int		q_start;
	int		arg_start;
	int		arg_end;
	int		word_start;
	int		word_end;
	int		flag;
	char 	quote_char;
	bool 	in_quotes;
	bool 	is_word;
}	t_split;

char	*create_path(char *command);
char	**ft_split_bash(char *input, char *delimeter);
void	assign_type(char *keyword, t_token *token, e_types type);
void	token_simple(char **result, t_shell *shell);

#endif
