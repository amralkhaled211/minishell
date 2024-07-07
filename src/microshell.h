/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:58:56 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 14:52:21 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>
# include <limits.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"

# define HEREDOC_NAME "/tmp/heredoc"

extern volatile sig_atomic_t	g_exit;

typedef enum e_types
{
	TOKEN_DEFAULT,
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARG,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	OUT_FILE,
	TOKEN_REDIRECT_IN,
	IN_FILE,
	TOKEN_APPEND,
	APPEND_FILE,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_END,
	TOKEN_DOLLAR
}	t_types;

typedef struct s_exp_pos
{
	bool	unset;
	bool	in_quote;
	int		start;
	int		end;
}	t_exp_pos;

typedef struct s_token
{
	bool		amb_redir;
	bool		do_split;
	bool		last_token;
	bool		expanded;
	t_types		type;
	char		*value;
	char		*orig_input;
	char		**var_splited;
	char		**array_exp;
	t_exp_pos	*exp_pos;
	int			j;
	int			a;
	bool		with_quote;
}	t_token;

typedef struct s_redirection
{
	t_types		type;
	char		*file;
	char		*docfl;
	int			input_fd;
	int			output_fd;
	bool		amb_redir;
	bool		with_quotes;
}	t_redirection;

typedef struct s_in_output
{
	int				i_o_fd;
	char			*file;
}	t_in_output;

typedef struct s_command
{
	char			*cmd_name;
	char			*path;
	char			**cmd_args;
	char			**args;
	t_redirection	*redirections;
	int				num_redirections;
	t_in_output		last_in;
	t_in_output		last_out;
	bool			no_file;
	bool			is_path;
	bool			p_err_msg;
	bool			q_removed;
	int				is_a_dir;
	bool			detected_amb;
	bool			is_built_in;
	bool			end_of_cmd;
}	t_command;

typedef struct s_flags
{
	bool	dollar_c_brack;
	int		cmd_flag;
	int		found_in;
	int		found_out;
}	t_flags;

typedef struct s_shell
{
	t_command	*command;
	t_token		*token;
	t_token		*n_token;
	char		**env;
	char		**export;
	char		**splited;
	int			num_tokens;
	int			num_pipes;
	long		exit_status;
	t_flags		flags;
	char		*current_dir;
	char		*old_dir;
	int			syntax_check;
	int			stdin_backup;
	int			stdout_backup;
	bool		sig_flag;
	int			last_exit_status;
}	t_shell;

typedef struct s_index
{
	int	a;
	int	b;
	int	c;
	int	d;
}	t_index;

typedef struct s_split
{
	char	**result;
	char	***exp_res;
	int		a;
	int		i;
	int		exp_i;
	int		num_words;
	int		q_start;
	int		arg_start;
	int		arg_end;
	int		word_start;
	int		word_end;
	int		flag;
	char	quote_char;
	bool	in_quotes;
	bool	is_word;
	int		processed;
}	t_split;

//here_doc parts
bool	is_spertor(char c);
char	*replace_str_heredoc(char *str, char *var_value, int index);
char	*delete_and_replace_for_doc(char *value, char *str, int ind);
char	*get_value_to_str(char *old_str, char *value, int len, int ind);
char	*make_str_from_tab(char **tab, char *line);
char	*ft_strjoin_doc(char *s1, char *s2, int spaces);
char	*add_spaces(int spaces, char *str);
int		count_first_spaces(char	*line);
int		count_spaces(char *line);

//mircoshell.c
char	*create_path(char *command);
void	setup_pipe(t_shell *shell, t_command *command);
int		parsing(t_shell *shell, char *input);
int		check_input(t_shell *shell, char *input);
void	setup_minishell(t_shell *shell, char *envp[]);
void	identify_built_ins(t_shell *shell, t_command *command);
void	prep_exec(t_shell *shell, t_command *command);
void	sort_export(t_shell *shell, char **env);

//signals.c
void	p_do_signal(void);
void	c_do_signal(void);
void	p_ignore_baskslash(void);
void	c_handle_backslash(void);
void	p_do_signal_after(void);

//expander
void	expander(t_shell *shell, t_token *token);
int		change_var_to_val(t_token *token, char *value, int ind, int i);
char	*delete_and_replace(t_token *token, char *str, char *value, int ind);
int		var_len(char *str);
bool	is_var_compliant(char c);
char	*valid_var(char *value, t_shell *shell);
void	free_ptr(void *ptr);
bool	is_var_val(char *var, t_shell *shell);
bool	inside_dquote(t_shell *shell, char *value, int j);
char	*get_the_var(char *str);
char	*get_var_only(char *str);
bool	range_quotes(char *str, int j);
bool	range_quotes_two(char *str, int j);
char	*get_value_from_var(char *var, t_shell *shell);
char	*mini_delete_var(char *var, char *new, int ind);
void	expand_checker(t_shell *shell, t_token *token, int i);
int		mini_get_var(char *str);
bool	no_quotes_outside(char *orig_input);
void	check_amb(t_shell *shell, t_token *token);

//bulit_in
int		echo(char **args, t_shell *shell);
int		env(t_shell *shell, char **args);
int		export(t_shell *shell, char **av);
int		pwd(t_shell *shell, char **args);
int		unset(t_shell *shell, char **args);
int		cd(t_shell *shell, char **args);
int		ft_exit(t_shell *shell, char **args);

//bulit_in utils
int		execute_built_in(t_shell *shell, t_command *cmd);
bool	is_valid_var_key(char *var);
char	**realloc_env_var(t_shell *shell, int size);
char	**realloc_export_var(t_shell *shell, int size);
int		get_var_count(char **env);
int		get_var_ind(char **env, char *var);
int		get_export_var_ind(char **env, char *var);
int		set_var(t_shell *shell, char *key, char *value);
bool	set_export_var_no_value(t_shell *shell, char *key);
int		set_export_var_with_value(t_shell *shell, char *key, char *value);
void	free_arry(char **arry);
char	*get_env_var_value(char **env, char *var);
bool	init_dir(t_shell *shell);
void	help_export(t_shell *shell, char *av, char **arry);
void	single_arg(t_shell *shell, char **args);
void	single_arg_sec(t_shell *shell, char **args);
int		plural_args(t_shell *shell, char **args);
void	cmp_orig_conv(t_shell *shell, char **args, char *original,
			char *converted);
char	*make_qoutes(char *str);
void	free_rest_export(char **new_env, int i);
void	mini_sort(char *arr[], int n);
int		ft_isspace(int c);
int		change_dir(t_shell *shell, char *path);
int		export_env(t_shell *shell);

//exit
bool	is_numeric(t_shell *shell, char *arg);
int		num_of_args(char **args);
char	*rm_zero(char *original);

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
size_t	count_words(char *s, t_split *split);
int		ft_pipe_special(char *input, char *delimeter, t_split *split);
int		ft_redir_special(char *input, char *delimeter, t_split *split);
int		ft_appdoc_special(char *input, char *delimeter, t_split *split);
char	**ft_split_bash(char *input, char *delimeter);
int		check_char(t_split *split, char *input, char *delimeter);
char	**before_end_split(t_split *split, char *input, char *delimeter);
int		quote_handling(t_split *split, char *input, char *delimeter);
int		handle_splitting(t_split *split, char *input, char *delimeter);
int		first_char_count(char *s, t_split *split, int i, int *count);
int		non_first_char_count(char *s, t_split *split, int i, int *count);
int		count_quote_part(char *s, t_split *split, int i, int *count);
int		count_helper(char *s, t_split *split, int i, int *count);

//token_simple.c
void	assign_type(t_shell *shell, char *keyword, t_types type, int i);
bool	identify_type_sim(t_shell *shell, char *keyword, t_token *token,
			int i);
void	analyze_result(char **input, t_shell *shell, int i);
int		token_simple(char **result, t_shell *shell);
bool	is_closed_quote(char *str);
void	default_token(t_token *token, int num);
int		f_syntax_check(t_shell *shell, char **result);
int		array_len(char **result);

//after_expansion.c
void	token_after_expansion(t_shell *shell, t_token *token);
int		add_tokens(t_shell *shell, t_token *n_token, t_token *token, int j);
int		copy_token(t_token *n_token, t_token *token);
int		get_size_n_token(t_token *token, int num_tokens);
void	token_split_exp(t_shell *shell, t_token *token);
int		update_exp_i(t_token *token, t_split *split, int i);
void	default_exp_pos(t_token *token);
bool	exp_in_quote(char *str, int a);

//ft_split_sec.c
char	**ft_split_sec(t_token *token, char *s, char *delimeter);
int		mini_split_sec(t_token *token, char *s, char *delimeter,
			t_split *split);
int		process_quote(t_token *token, char *s, char *delimeter,
			t_split *split);
int		split_last_part(t_token *token, char *s, char *delimeter,
			t_split *split);
void	freeing(char **result, int j);
int		get_token_q(t_token *token, char *s, char *delimeter, t_split *split);
int		get_token_two(t_token *token, char *s, char *delimeter,
			t_split *split);
int		get_end_q(t_token *token, char *s, char *delimeter, t_split *split);
int		get_start_q(t_token *token, char *s, char *delimeter, t_split *split);
int		get_start(t_token *token, char *s, char *delimeter, t_split *split);
int		get_end(t_token *token, char *s, char *delimeter, t_split *split);
bool	is_exp(t_token *token, t_split *split, int i);
int		joining_exp_end(t_token *token, t_split *split, int start);
int		joining_exp_beg(t_token *token, t_split *split);
void	free_3d_array(t_split *split, int j);

//token_advance.c
int		init_command(t_shell *shell, t_command *command, int i, int *b);
void	count_pipes_and_allocate(t_shell *shell, t_token *token);
void	default_command(t_shell *shell, t_command *command, int num_pipes);
void	default_last_io(t_command *command);
int		token_adv(t_shell *shell, t_token *token);
void	check_ambig_redir(t_shell *shell, t_command *command);
int		is_redir(t_token token);
int		is_file(t_token token);
int		check_syntax(t_shell *shell, t_command *command, t_token *token);
bool	last_token_pipe(t_token *token);
void	default_cmd_redir(t_shell *shell, t_command *command, int i,
			int num_pipes);
void	default_cmd_args(t_shell *shell, t_command *command, int i,
			int num_pipes);
void	default_cmd_flags(t_command *command);
int		get_cmd_name(t_shell *shell, t_command *command, int i, int *a);
int		get_cmd_args(t_shell *shell, t_command *command, int i, int *a);
int		get_cmd_redir(t_shell *shell, t_command *command, int i, int *b);
bool	check_syn_sim_one(t_shell *shell, t_token *token, int i);
bool	check_syn_sim_two(t_shell *shell, t_token *token, int i);
int		cound_cmd_redir(t_shell *shell, int cmd_nr);
bool	is_pos_existing(char *value, int i);
bool	is_file_word_pipe(t_token *n_token);
int		assign_cmd_name(t_shell *shell, t_command *command, int i, int *a);
bool	is_cmd_arg_file_word(t_token *n_token);

//handle_path.c
void	handle_path(t_shell *shell, t_command *command);
bool	is_path(char *str);
void	update_cmd_name(t_shell *shell, t_command *command);
char	*extract_cmd_name(t_shell *shell, char *str);
void	set_path(t_shell *shell, t_command *command);
char	*add_slash(char *str);
void	mini_set_path(t_shell *shell, t_command *command, char **s_path,
			char *tmp_cmd_name);

//before_exec.c
void	remove_quotes(t_shell *shell, t_command *command);
char	*handle_quotes(t_shell *shell, char *input, int usage);
void	create_args(t_shell *shell, t_command *command);
char	**join_cmd_args(t_shell *shell, t_command *command, int n);
int		get_size_str_array(char **args);
void	rm_quotes_args(t_shell *shell, t_command *command);
void	rm_quotes_redir(t_shell *shell, t_command *command);
void	mini_handle_quote(char *input, char *result, int len);
bool	with_quote(char *str);
void	quote_removal(t_shell *shell, t_token *token);

//setup_redir
void	setup_redir(t_shell *shell, t_command *command);
void	init_last_io(t_shell *shell, t_command *command,
			t_redirection *redirec);
int		get_fd(t_shell *shell, t_command *command, t_redirection *redirec);
int		handle_redir_out_append(t_shell *shell, t_command *command,
			t_redirection *redirec);
int		handle_here_doc(t_shell *shell, t_command *command,
			t_redirection *redirec);
int		handle_redir_in(t_shell *shell, t_command *command,
			t_redirection *redirec);
int		type_redir(t_redirection *redirec);
int		redir_in_out(t_redirection *redirec);
int		check_file_perm(t_command *command, t_redirection *redirec,
			char *file_path);
char	*get_file_path(t_shell *shell, char *file);
int		mini_redir_msg(t_shell *shell, t_command *command,
			t_redirection *redirec);

//make_doc.c
char	*get_heredoc_name(void);
int		check_heredoc_line(t_shell *shell, char **line, t_redirection *io,
			int *ret);
int		fill_heredoc(t_shell *shell, t_redirection *io, int fd);
int		open_heredoc(t_shell *shell, t_redirection	*io);
int		check_heredoc_special(char **line, t_redirection *io, int *ret);
//int	delete_var_doc(char *orig, int ind);

//expand_doc.c
char	*doc_expand(t_shell *shell, char *line);
char	*var_expander_heredoc(t_shell *shell, char *str);

//begin_execution.c
void	begin_execution(t_shell *shell, t_command *command);
bool	is_built_in(t_command *cmd);
int		prep_redir(t_shell *shell, t_command *command, int i);
void	multi_cmd(t_shell *shell, pid_t *child_pid, int **pfd);
int		single_built_in(t_shell *shell, t_command *command);

//handle_execution.c
void	handle_execution(t_shell *shell, pid_t *child_pid, int **pfd, int i);
void	input_redir_handler(t_shell *shell, int **pfd, int i);
void	output_redir_handler(t_shell *shell, int **pfd, int i);
void	file_error_handling(t_shell *shell, int **pfd, int i);
void	mini_handle_exec(t_shell *shell, int **pfd, int i);
int		is_directory(char *path);
void	file_not_exec(t_shell *shell, int **pfd, int i);
void	clean_exec_part(int **pfd, pid_t *child_pid, int flag_free);
void	is_a_dir(t_shell *shell, int **pfd, int i);
void	main_exec_child(t_shell *shell, pid_t *child_pid, int **pfd, int i);
void	close_after_fork(t_shell *shell, int **pfd, int i);
void	close_all_fds(t_shell *shell);
char	*file_not_exec2(t_shell *shell, int i);
char	*file_error_handling2(t_shell *shell, int i, char *path_env);
void	is_not_a_dir(t_shell *shell, int **pfd, int i);

//cleanup.c
void	free_str_array(char **array);
void	free_token_array(t_token *token);
void	free_after_syntax_error(t_shell *shell, int stage);
void	free_split_fail(t_split *split, int a);
void	free_after_malloc_fail(t_shell *shell, int f, int stage);
void	prep_next_cmd(t_shell *shell);
void	free_before_exit(t_shell *shell);
void	free_env_fail(t_shell *shell, int m);
void	free_cmd_table(t_shell *shell, t_command *command, int f);
void	close_fds(t_shell *shell);
void	free_cmd_redir(t_command *command, int i);
void	free_cmd_args(t_command *command, int i);
void	free_dir_fail(t_shell *shell, int stage);
void	free_malloc_fail_stage_1(t_shell *shell, int f);
void	free_malloc_fail_stage_2(t_shell *shell, int f);
void	free_malloc_fail_stage_3(t_shell *shell, int f);
void	free_malloc_fail_stage_4(t_shell *shell, int f);
void	free_malloc_fail_stage_5(t_shell *shell, int f);

//messages.c
void	my_sprintf(char *buffer, const char *format, const char *insert);
int		cmd_printf(char *detail, char *error_msg, char *command, int error_nb);

//testing.c
void	print_cmd_table(t_command *command);
void	print_tokens(t_shell *shell);
void	print_split_result(char **splited);
void	print_n_tokens(t_shell *shell);

#endif