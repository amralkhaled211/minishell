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
# include <fcntl.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define MAX_ARGS	128		// Maximum number of arguments
# define MAX_CMD	128
# define MAX_TOKENS	350
# define MAX_REDIR	128
# define MAX_VAR	128
# define HEREDOC_NAME "/tmp/heredoc"

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
	char	*docfl;
	int		output_fd;
	bool	amb_redir;
}	t_redirection;

typedef struct s_in_output
{
	int				i_o_fd;
	int				stdin_backup;
	int				stdout_backup;
	char			*file;
}	t_in_output;

typedef struct s_command
{
	char			*cmd_name;						// first input and each after a pipe
	char			*path;						//FREE!!!!
	char			*args[MAX_ARGS];				// Arguments array
	char			**cmd_args;					//!!!!!!!FREE SECTION!!!!!!
	t_redirection	redirections[MAX_REDIR];		// Array of redirections
	int				num_redirections;				// Number of redirections
	t_in_output		last_in;
	t_in_output		last_out;
	bool			no_file;
	bool			p_err_msg;
	bool			end_of_cmd;						//like TOKEN_END, show end
}	t_command;

/* 	bool			pipe_send;						//Pipes
	bool			pipe_recieve; */
/*
	int				num_args;						// Number of arguments
	int				num_redir_in;
	int				num_redir_out;
*/

typedef struct s_flags
{
	bool	dollar_c_brack;		//String can continue after c_bracket, not used yet
	int		cmd_flag;			//used in token_advance
	int		found_in;
	int		found_out;
}	t_flags;

typedef struct s_shell
{
	t_command	*command;	//second after tokens, use tokens to create the commands, and use them to create an AST, if necessary
	t_token		token[MAX_TOKENS];	// first fill tokens, get num_of_tokens
	char		**env;
	char		**splited;
	int			num_pipes;
	t_flags		flags;			//always init before use
	int			syntax_check;
}	t_shell;

	//int			num_of_commands;

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
void	setup_pipe(t_shell *shell, t_command *command);

//expander
void	expander(t_shell *shell, t_token *token);
int		change_var_to_val(t_token *token, char *value, int ind, int i);
char	*delete_and_replace(t_token *token, char *str, char *value, int ind, int i);
int		var_len(char *str);
bool	is_var_compliant(char c);
char 	*valid_var(char *value, t_shell *shell);
void	free_ptr(void *ptr);
bool	is_var_val(char *var, t_shell *shell);
char	*replace_str_heredoc(char *str, char *var_value, int index);
char	*delete_and_replace_for_doc(char *value, char *str, int ind);
char	*var_expander_heredoc(t_shell *shell, char	*str);

//bulit_in
int	echo(char **args);
int	env(t_shell *shell, char **args);
int	export(t_shell *shell, char **av);
int	pwd(t_shell *shell);
int unset(t_shell *shell, char **args);
//int cd(t_shell *shell, char **args);

//bulit_in utils
bool	is_valid_var_key(char *var);
char	**realloc_env_var(t_shell *shell, int size);
int		get_var_count(char **env);
int		get_var_ind(char **env, char *var);
bool	set_var(t_shell *shell,  char *key, char *value);
void	free_arry(char **arry);
char	*get_env_var_value(char **env, char *var);
bool	init_dir(t_shell *shell);
//void	free_ptr(void *ptr);



//here_doc
char	*get_heredoc_name(void);
int		fill_heredoc(t_shell *shell, t_redirection *io, int fd);
int		check_heredoc_line(t_shell *shell, char **line, t_redirection *io, int *ret);
int		open_heredoc(t_shell *shell,t_redirection	*io);
char	*doc_expand(t_shell *shell, char *line);


//shell_prep.c
void	copy_env(char **envp, t_shell *shell);
void	init_all_shell(t_shell *shell);
void	init_flags(t_flags *flags);

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
void	default_last_io(t_command *command);
int		token_adv(t_shell *shell, t_token *token);
void	check_ambig_redir(t_command *command);
int		is_redir(t_token token);
int		is_file(t_token token);
int		check_syntax(t_shell *shell, t_command *command, t_token *token);
bool	last_token_pipe(t_token *token);

//handle_path.c
void	handle_path(t_shell *shell, t_command *command);
bool	is_path(char *str);
void	update_cmd_name(t_shell *shell, t_command *command);
char	*extract_cmd_name(t_shell *shell, char *str);
void	set_path(t_shell *shell, t_command *command);
char	*add_slash(char *str);

//setup_redir
void	setup_redir(t_shell *shell, t_command *command);
void	init_last_io(t_shell *shell, t_command *command, t_redirection *redirec);
int		get_fd(t_shell *shell, t_command *command, t_redirection *redirec);

//setup_pipe
void	setup_pipe(t_shell *shell, t_command *command);

//cleanup.c
void	free_str_array(char **array);
void	free_token_array(t_token *token);
void	free_after_syntax_error(t_shell *shell, int stage);
void	free_split_fail(t_split *split, int a);
void	free_after_malloc_fail(t_shell *shell, int f, int stage);
void	prep_next_cmd(t_shell *shell);
void	free_before_exit(t_shell *shell);
void	free_env_fail(t_shell *shell, int m);
void	free_cmd_table(t_shell *shell, t_command *command);

//before_exec.c
void	remove_quotes(t_shell *shell, t_command *command);
char	*handle_quotes(t_shell *shell, char *input);
void	create_args(t_shell *shell, t_command *command);
char	**join_cmd_args(t_shell *shell, t_command *command, int n);
int		get_size_args(char **args);

//messages.c
void	my_sprintf(char *buffer, const char *format, const char *insert);

//testing.c
void	print_cmd_table(t_command *command);
void	print_tokens(t_shell *shell);
void	print_split_result(char **splited);

#endif
