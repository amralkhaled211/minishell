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
*/

int main(int ac, char *av[], char *envp[])
{
	//char **arguments;
	t_shell	shell;
	int status = 0;
	char *input;
	char *path;
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
			free_str_array(shell.env);
			break;
		}
		if (*input == 0)
			continue;
		if (*input)
			add_history(input);
		shell.splited = ft_split_bash(input, " ");
		if (!shell.splited)
			return (perror("shell.splited is NULL"), free_str_array(shell.env), 1);
		shell.syntax_check = token_simple(shell.splited, &shell);
		if (shell.syntax_check)
		{
			free_after_syntax_error(&shell, 1);//free before next cmd
			continue ;
		}
		//printf("BEFORE EXPANSION\n");
		//print_tokens(&shell);
		expander(&shell, shell.token);
		//printf("AFTER EXPANSION\n");
		//print_tokens(&shell);
		shell.syntax_check = token_adv(&shell, shell.token);
		if (shell.syntax_check)
		{
			free_after_syntax_error(&shell, 2);//free before next cmd
			continue ;
		}
		//printf("	BEFORE QUOTE DELETION:\n");
		//print_cmd_table(shell.command);
		remove_quotes(&shell, shell.command);
		//printf("	AFTER QUOTE DELETION:\n");
		print_cmd_table(shell.command);
		path = create_path(shell.command[0].cmd_name);
		int child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(path, shell.command[0].args, envp) == -1)
			{
				perror("exit");
				exit(EXIT_FAILURE);
			}
		}
		waitpid(child_pid, &status, 0);
		//free before next cmd
		free(path);
		prep_next_cmd(&shell);//prep for next command
	}
	//free_all(&shell);
	//free_before_exit(&shell);
	free(input);
    return (0);
}

char	*create_path(char *command)
{
	char *path = "/bin/";
	//char *path = "/nfs/homes/aismaili/minishell/src/";
	int i = -1;
	int j = 0;

	char *result = malloc (ft_strlen(command) + ft_strlen(path) + 1);
	while (path[++i])
		result[i] = path[i];
	while (command[j])
		result[i++] = command[j++];
	result[i] = 0;
	return (result);
}