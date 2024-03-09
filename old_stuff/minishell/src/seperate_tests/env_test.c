#include <stdio.h>
#include "microshell.h"

void	copy_env(char **envp, t_shell *shell);

int main(int argc, char *argv[], char *envp[])
{
	t_shell	shell;
	int		i;

	i = 0;
	copy_env(envp, &shell);
	while (shell.env[i])
	{
		printf("%s\n", shell.env[i]);
		i++;
	}
}

void	copy_env(char **envp, t_shell *shell)
{
	int		i;
	int		d;
	char	*num;

	i = 0;
	while (envp[i])
		i++;
	shell->env = malloc(sizeof(char *) * i + 1);
	if (!shell->env)
		free_env();//just exit
	i = -1;
	while (envp[++i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (strncmp(shell->env[i], "SHLVL", 5) == 0)//increment the SHLVL
		{
			d = ft_atoi(&shell->env[i][6]) + 1;
			free(shell->env[i]);
			num = ft_itoa(d);
			if (!num)
				free_env();
			shell->env[i] = malloc(7 + ft_strlen(num));
			if (!shell->env[i])
				free_env();//free all the allocated env
			shell->env[i] = ft_strjoin("SHLVL=", num);
		}
	}
	shell->env[i] = ft_strdup(envp[i]);
}
