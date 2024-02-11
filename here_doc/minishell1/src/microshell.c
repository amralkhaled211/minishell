#include "microshell.h"

/*
valgrind --leak-check=full --show-leak-kinds=all ./microshell

valgrind --suppressions=file.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --track-fds=yes --trace-children=yes ./microshell

valgrind --suppressions=updated_file.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --show-mismatched-frees=yes --read-var-info=yes --track-fds=yes --trace-children=yes ./microshell

*/
/*
EXPANDER: cases with invalid read
ls $HOME$USER$VAR$HOME laskdfj
ls $HOME$USER$VAR$HOME laskdfj asldfj alsdf aslfj > out
since we use buffer, it is good practice to set a limit for the no. of tokens accepted
*/

int main(int ac, char *av[], char *envp[])
{
	//char **arguments;
	t_shell	shell;
	char	*input;
	//char *path;
	((void)ac, (void)av);
	init_all_shell(&shell);
	copy_env(envp, &shell);
	//copy the env
	//update the env when necessary
	while (1)
	{
		init_all_shell(&shell);
		input = readline("microshell $ ");
		if (!input || strcmp(input, "exit") == 0)// cases: "exit nonesense" need to be handled
		{
			write(1, "exit\n", 6);
			break ;
		}
		if (*input == 0)
			continue ;
		if (*input)
			add_history(input);
		shell.splited = ft_split_bash(input, " ");
		if (!shell.splited)
			return (perror("shell.splited is NULL"), free_str_array(shell.env), 1);
		//print_split_result(shell.splited);
		shell.syntax_check = token_simple(shell.splited, &shell);//protected
		if (shell.syntax_check)
		{
			free_after_syntax_error(&shell, 1);//free before next cmd
			continue ;
		}
		//printf("BEFORE EXPANSION\n");
		//print_tokens(&shell);
		expander(&shell, shell.token);//PROTECTIONS!!!
		//printf("AFTER EXPANSION\n");
		//print_tokens(&shell);
		shell.syntax_check = token_adv(&shell, shell.token);//protected
		if (shell.syntax_check)
		{
			free_after_syntax_error(&shell, 2);//free before next cmd
			continue ;
		}
		//printf("	BEFORE QUOTE DELETION:\n");
		//print_cmd_table(shell.command);
		remove_quotes(&shell, shell.command);//protected
		//printf("	AFTER QUOTE DELETION:\n");
		//print_cmd_table(shell.command);
		handle_path(&shell, shell.command);//PROTECTIONS!!
		create_args(&shell, shell.command);//protected
		setup_redir(&shell, shell.command);//PROTECTIONS!!
		setup_pipe(&shell, shell.command);//PROTECTIONS!!
		//free before next cmd
		prep_next_cmd(&shell);//prep for next command
	}
	//free_all(&shell);
	free_before_exit(&shell);
	free(input);
	return (0);
}

int	excute_built_in(t_shell *shell, t_command *cmd)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd->cmd_name, "echo", 5) == 0)
		res = echo(cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		res = env(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "export", 7) == 0)
		res = export(shell, cmd->args);
	else if (ft_strncmp(cmd->cmd_name, "pwd", 4) == 0)
		res = pwd(shell);
	else if (ft_strncmp(cmd->cmd_name, "unset", 6) == 0)
		res = unset(shell, cmd->args);
	//else if (ft_strncmp(cmd->cmd_name, "cd", 3) == 0)
	//	res = cd(shell, cmd->args);
	else
		printf("command not found!!!\n");
	return (res);
}

/* char	*create_path(char *command)
{
	char *path = "/bin/";
	//char *path = "/nfs/homes/aismaili/minishell/src/";
	int i = -1;
	int j = 0;

	char *result = malloc(ft_strlen(command) + ft_strlen(path) + 1);
	while (path[++i])
		result[i] = path[i];
	while (command[j])
		result[i++] = command[j++];
	result[i] = 0;
	return (result);
} */

/* void	setup_pipe(t_shell *shell, t_command *command)//testing only for two commands
{
	int		pfd[2];
	int		child_pid;
	int		child_pid2;
	int		status;

	printf("IN SETUP PIPE\n");
	if (pipe(pfd) == -1)
		perror("pipe fail");//exit and free
	child_pid = fork();
	if (child_pid == -1)
		perror("fork fail");//exit and free
	if (child_pid == 0)//first command will write to pfd[1]
	{
		close(pfd[0]);//close unused read end
		dup2(pfd[1], STDOUT_FILENO);
		execve(command[0].path, command[0].cmd_args, shell->env);
		close(pfd[1]);
	}
	else
	{
		child_pid2 = fork();
		if (child_pid2 == -1)
			perror("fork fail");//exit and free
		if (child_pid2 == 0)//second command will read from pfd[1]
		{
			close(pfd[1]);//close unused write end
			dup2(pfd[0], STDIN_FILENO);//redirect from stdin to pfd[0] for the input
			execve(command[1].path, command[1].cmd_args, shell->env);
			close(pfd[0]);
		}
		else
		{
			close(pfd[0]);
			close(pfd[1]);
			waitpid(child_pid, &status, 0);
			waitpid(child_pid2, &status, 0);
		}
	}
} */

/* int child_pid = fork();
		int status = 0;
		if (child_pid == 0)
		{
			if (execve(shell.command[0].path, shell.command[0].cmd_args, envp) == -1)
			{
				//free here
				perror("exit");//maybe command not found
				exit(EXIT_FAILURE); 
			}
		} */
		//waitpid(child_pid, &status, 0);
		//path = create_path(shell.command[0].cmd_name);


