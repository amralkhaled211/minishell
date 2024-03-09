#include "microshell.h"

int main(int ac, char *av[], char *envp[])
{
	char **arguments;
	t_shell	shell;
	int status = 0;
	char *input;
	char *path;
	((void)ac, (void)av);
	//copy the env
	//update the env when necessary
	while (1)
	{
		input = readline("microshell $ ");
		if (!input || strcmp(input, "exit") == 0)// cases: "exit nonesense" need to be handled
		{
			write(1, "exit\n", 6);
			break;
		}
		if (*input == 0)
			continue;
		if (*input)
			add_history(input);
		arguments = ft_split_bash(input, " ");
		//printf("argument: %s\n", arguments[0]);
		token_simple(arguments, &shell);
		//parsing starts: recognize tokens
		path = create_path(arguments[0]);
		int child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(path, arguments, envp) == -1)
			{
				perror("ex");
				exit(EXIT_FAILURE);
			}
		}
		waitpid(child_pid, &status, 0);
	}
	free(input);
    return 0;
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
	{
		result[i++] = command[j++];
	}
	result[i] = 0;
	return (result);
}
