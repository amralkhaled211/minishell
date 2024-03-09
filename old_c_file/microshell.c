#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char	**ft_split(char const *s, char c);
char	*create_path(char *command);
size_t	ft_strlen(const char *s);

int main(int ac, char *av[], char *envp[]) {
    //char *const program = "/bin/ls";
    char **arguments;/*  = { "ls", "-l", NULL }; */
    //char *const environment[] = { "TERM=xterm-256color", NULL };
    int *status;
	char *input;
	char *path;

	while (1)
	{
		input = readline("microshell $ ");
		if (!input || strcmp(input, "exit") == 0) {
        	free(input);
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
		waitpid(child_pid, status, 0);
	}
	free(input);
    return 0;
}

char	*create_path(char *command)
{
	char *path = "/bin/";
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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			b;
	unsigned char	*sub;

	i = 0;
	b = 0;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	sub = malloc(((len + 1) * sizeof(char)));
	if (sub == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && b < len)
			sub[b++] = s[i];
		i++;
	}
	sub[b] = '\0';
	return ((char *)sub);
}

static void	*freeing(char **result, size_t x)
{
	size_t	i;

	i = 0;
	while (i < x)
	{
		free(result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			j++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	begin;
	size_t	end;
	size_t	i;

	begin = 0;
	i = 0;
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (i < count_words(s, c))
	{
		while (s[begin] == c)
			begin++;
		end = begin;
		while (s[end] != c && s[end] != '\0')
			end++;
		result[i] = ft_substr(s, begin, (end - begin));
		if (!result[i])
			return (freeing(result, i));
		begin = end;
		i++;
	}
	result[i] = 0;
	return (result);
}