#include "microshell.h"

int main(int ac, char *av[], char *envp[])
{
	//char *const program = "/bin/ls";
	char **arguments;/*  = { "ls", "-l", NULL }; */
	//char *const environment[] = { "TERM=xterm-256color", NULL };
	int status = 0;
	char *input;
	char *path;
	((void)ac, (void)av);
	while (1)
	{
		input = readline("microshell $ ");
		if (!input || strcmp(input, "exit") == 0) {
			write(1, "exit\n", 6);
			break;
		}
		if (*input == 0)
			continue;
		if (*input) {
			add_history(input);
		}
		arguments = ft_split(input, ' ');
		path = create_path(arguments[0]);
		int child_pid = fork();
		if (child_pid == 0)
		{
			if (execve(path, arguments, envp) == -1) {
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
