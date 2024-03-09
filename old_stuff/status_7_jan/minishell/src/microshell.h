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

# define MAX_ARGS 128  // Maximum number of arguments
# define REDIRECT_IN  "<"
# define REDIRECT_OUT ">"
# define REDIRECT_APPEND ">>"
# define REDIRECT_HEREDOC "<<"
# define PROMT  "microshell $ "
typedef struct s_redirection {
    char *type;    // REDIRECT_IN, REDIRECT_OUT, REDIRECT_APPEND, or REDIRECT_HEREDOC
    char *file;    // Filename for redirection, or delimiter for here-document
    //char *heredoc; // Buffer to store the here-document content (if needed)
}   t_redirection;

typedef struct s_pipe
{
	char	*pipe;
}   t_pipe;

typedef struct s_command {
    char			*cmd;				// Command name
    char			*args[MAX_ARGS];	// Arguments array
    t_redirection	*redirections;		// Array of redirections
	t_pipe			*pipes;				//Pipes
    int				num_args;			// Number of arguments
    int				num_redirections;	// Number of redirections
	
}   t_command;

typedef struct s_command_line {
	t_command *commands;  // Array of command structures
	int num_commands;	 // Number of commands in the pipeline
}   t_command_line;

char	*create_path(char *command);

#endif