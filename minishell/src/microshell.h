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
# include <errno.h>
# include "../libft/libft.h"

# define MAX_ARGS	128		// Maximum number of arguments
# define MAX_CMD	128
# define MAX_TOKENS	350
# define MAX_REDIR	128
# define MAX_VAR	128

typedef enum en_types
{
	TOKEN_DEFAULT,
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,			// |
	TOKEN_REDIRECT_OUT,	// >
	OUT_FILE,
	TOKEN_REDIRECT_IN,	// <
	IN_FILE,
	TOKEN_APPEND,		// >>
	APPEND_FILE,
	TOKEN_HEREDOC,		// <<
	TOKEN_EOF,
	TOKEN_FILE,
	TOKEN_DOLLAR,
	TOKEN_END			// End of input, value NULL
}	e_types;

typedef struct s_token
{
	bool	amb_redir;
	e_types	type;
	char	*value;
}	t_token;

typedef struct s_redirection
{
	e_types	type;		// REDIRECT_IN, REDIRECT_OUT, REDIRECT_APPEND, or REDIRECT_HEREDOC
	char	*file;		// Filename for redirection, or delimiter for here-document
	int		input_fd;
	int		output_fd;
}	t_redirection;

typedef struct s_command
{
	char			*cmd_name;						// first input and each after a pipe
	char			*args[MAX_ARGS];				// Arguments array
	t_redirection	redirections[MAX_REDIR];		// Array of redirections
	bool			end_of_cmd;						//like TOKEN_END, show end
	bool			pipe_send;						//Pipes
	bool			pipe_recieve;
}	t_command;

/*
	int				num_args;						// Number of arguments
	int				num_redirections;				// Number of redirections
	int				num_redir_in;
	int				num_redir_out;
*/

typedef struct s_flags
{
	bool	dollar_c_brack;		//String can continue after c_bracket, not used yet
	int		cmd_flag;			//used in token_advance
}	t_falgs;

typedef struct s_shell
{
	t_command	*command;	//second after tokens, use tokens to create the commands, and use them to create an AST, if necessary
	t_token		token[MAX_TOKENS];	// first fill tokens, get num_of_tokens
	//int			num_of_commands;
	char		**env;
	char		**splited;
	t_falgs		flags;			//always init before use
	int			syntax_check;
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

//mircoshell.c
char	*create_path(char *command);

//expander
void	expander(t_shell *shell, t_token *token);
int		change_var_to_val(t_token *token, char *value, int ind, int i);
char	*delete_and_replace(t_token *token, char *str, char *value, int ind, int i);
int		var_len(char *str);
bool	is_var_compliant(char c);
char 	*valid_var(char *value, t_shell *shell);
void	free_ptr(void *ptr);

//shell_prep.c
void	copy_env(char **envp, t_shell *shell);
void	init_all_shell(t_shell *shell);

//split_bash.c
void	reset_split_var(t_split *split);
int		ft_get_redir(char *input, int i, t_split *split);
int		is_op_special(char *input, int i, t_split *split);
void	init_start_end(t_split *split, char *input, char *delimeter);
int		is_quote(char c);
int		save_quote(t_split *split, char *input, char *delimeter);
int		save_word(t_split *split, char *input, char *delimeter);
int		pipe_special(int *count, char *delimeter, char *s, int i);
int		redir_special(int *count, char *delimeter, char *s, int i);
int		appdoc_special(int *count, char *delimeter, char *s, int i);
size_t	count_words(char *s, char *delimeter, t_split *split);
int		ft_pipe_special(char *input, char *delimeter, t_split *split);
int		ft_redir_special(char *input, char *delimeter, t_split *split);
int		ft_appdoc_special(char *input, char *delimeter, t_split *split);
char	**ft_split_bash(char *input, char *delimeter);

//token_simple.c
void	assign_type(t_shell *shell, char *keyword, e_types type, int i);
bool	identify_type_sim(t_shell *shell, char *keyword, t_token *token, int i);
void	analyze_result(char **input, t_shell *shell, int i);
int		token_simple(char **result, t_shell *shell);
bool	is_closed_quote(char *str);

//token_advance.c
void	init_command(t_shell *shell, t_token *token, t_command *command, int i);
int		count_pipes(t_token *token);
void	default_command(t_command *command, int num_pipes);
int		token_adv(t_shell *shell, t_token *token);
void	check_ambig_redir(t_token *token);
int		is_redir(t_token token);
int		check_syntax(t_shell *shell, t_command *command, t_token *token);
bool	last_token_pipe(t_token *token);

//cleanup.c
void	free_str_array(char **array);
void	free_token_array(t_token *token);
void	free_cmd_table(t_shell *shell, t_command *command);
void	free_after_syntax_error(t_shell *shell, int stage);
void	free_split_fail(t_split *split, int a);
void	free_after_malloc_fail(t_shell *shell, int f, int stage);
void	prep_next_cmd(t_shell *shell);
void	free_before_exit(t_shell *shell);
void	free_env_fail(t_shell *shell, int m);

//before_exec.c
void	remove_quotes(t_shell *shell, t_command *command);
char	*handle_quotes(t_shell *shell, char *input);

//messages.c
void my_sprintf(char *buffer, const char *format, const char *insert);

//testing.c
void	print_cmd_table(t_command *command);
void	print_tokens(t_shell *shell);

#endif