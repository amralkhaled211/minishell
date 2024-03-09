/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_advance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:22:32 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/09 14:46:36 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

/*
handle expansion, look at notes;

flag for bash: $VAR: ambiguous redirect

*/

void	init_command(t_shell *shell, t_token *token, t_command *command, int i)
{
	static int	a;
	static int	b;

	if (i == 0 && shell->flags.cmd_flag == 0 && token[i].value && token[i].type == TOKEN_WORD)//take the expansion into consideration
	{
		command->cmd_name = ft_strdup(token[i].value);
		if (!command->cmd_name)
		{
			free_after_malloc_fail(shell, -1, 3);
		}
		token[i].type = TOKEN_COMMAND;
		shell->flags.cmd_flag = 1;//command_name found
		a = 0;
		b = 0;
	}
	else if (i > 0 && shell->flags.cmd_flag == 0 && token[i].value && token[i].type == TOKEN_WORD && (is_file(token[i - 1]) || token[i - 1].type == TOKEN_PIPE))
	{
		//init_cmd
		command->cmd_name = ft_strdup(token[i].value);
		if (!command->cmd_name)
		{
			free_after_malloc_fail(shell, -1, 3);
		}
		token[i].type = TOKEN_COMMAND;
		shell->flags.cmd_flag = 1;
		a = 0;
		b = 0;
	}
	else if (i > 0 && shell->flags.cmd_flag == 1 && token[i].type == TOKEN_WORD && (token[i - 1].type == TOKEN_COMMAND || token[i - 1].type == TOKEN_ARG || is_file(token[i - 1])))
	{
		//arguments
		command->args[a] = ft_strdup(token[i].value);//array is null-terminated, before all were set to null
		if (!command->args[a])
		{
			free_after_malloc_fail(shell, -1, 3);
		}
		token[i].type = TOKEN_ARG;
		a++;
	}
	else if (i > 0 && token[i].type == TOKEN_WORD && is_redir(token[i - 1]))
	{
		//redirections and heredoc
		command->redirections[b].file = ft_strdup(token[i].value);
		if (!command->redirections[b].file)
		{
			free_after_malloc_fail(shell, -1, 3);
		}
		token[i].type = token[i - 1].type + 1;
		command->redirections[b].type = token[i - 1].type;
		command->redirections[b].amb_redir = token[i].amb_redir;
		b++;
	}
	else if (token[i].type == TOKEN_END)//mark the end with end_of_cmd
	{
		command->cmd_name = NULL;
		command->args[a] = NULL;
		command->end_of_cmd = true;
	}
}

int	is_file(t_token token)
{
	if (token.type == IN_FILE)
		return (1);
	if (token.type == OUT_FILE)
		return (2);
	if (token.type == APPEND_FILE)
		return (3);
	if (token.type == TOKEN_EOF)
		return (4);
	return (0);
}

int	count_pipes(t_token *token)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (&token[i] && token[i].value)
	{
		if (token[i].type == TOKEN_PIPE)
			n++;
		i++;
	}
	return (n);
}

void	default_command(t_command *command, int num_pipes)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < (num_pipes + 2))
	{
		command[i].cmd_name = NULL;
		command[i].path = NULL;
		j = -1;
		while (++j < MAX_ARGS)
			command[i].args[j] = NULL;
		command[i].cmd_args = NULL;
		j = -1;
		while (++j < MAX_REDIR)
		{
			command[i].redirections[j].type = TOKEN_DEFAULT;
			command[i].redirections[j].input_fd = TOKEN_DEFAULT;
			command[i].redirections[j].output_fd = TOKEN_DEFAULT;
			command[i].redirections[j].file = NULL;
		}
		default_last_io(&command[i]);
		command[i].no_file = false;
		command[i].p_err_msg = false;
		command[i].end_of_cmd = false;
		i++;
	}
}

void	default_last_io(t_command *command)
{
	command->last_in.file = NULL;
	command->last_in.i_o_fd = -2;
	command->last_in.stdin_backup = -2;
	command->last_in.stdout_backup = -2;
	command->last_out.file = NULL;
	command->last_out.i_o_fd = -2;
	command->last_out.stdin_backup = -2;
	command->last_out.stdout_backup = -2;
}

int	token_adv(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	shell->num_pipes = count_pipes(token);
	shell->command = malloc(sizeof(t_command) * (shell->num_pipes + 2));
	if (!shell->command)
		free_after_malloc_fail(shell, -1, 2);//free
	default_command(shell->command, shell->num_pipes);
	shell->flags.cmd_flag = 0;
	while (token[i].value)
	{
		init_command(shell, token, &shell->command[j], i);
		if (token[i + 1].type == TOKEN_PIPE)
		{
			j++;
			shell->flags.cmd_flag = 0;//looking for cmd_name
		}
		i++;
	}
	j++;
	init_command(shell, token, &shell->command[j], i);
	return (check_syntax(shell, shell->command, shell->token));
}

//no command found - syntax error

/*	syntax error comes before ambig error	*/

/* void	check_ambig_redir(t_token *token)//return nothing, because the rest is executed
{
	int		i;
	char	*buffer;

	i = 0;
	while (token[i].type != TOKEN_END)
	{
		//check ambiguous redirection flag & go on with the rest of cmds
		if (token[i].amb_redir)//not a syntax error
		{
			get_command();
			//exec part: no redir will happen for this command
			//must pass NULL to next cmd
			printf("token[%i].value: %s\n", i, token[i].value);
			buffer = malloc(ft_strlen(token[i].value) + 50);
			//char buffer[100];
			my_sprintf(buffer, "minishell: %s: ambiguous redirect", token[i].value);//print once for each command
			ft_putendl_fd(buffer, 2);//print one time for each command
			free(buffer);
			//perror(buffer);//better use for system fail messages
		}
		i++;
	}
} */

int	is_redir(t_token token)
{
	if (token.type == TOKEN_REDIRECT_IN)
		return (1);
	if (token.type == TOKEN_REDIRECT_OUT)
		return (2);
	if (token.type == TOKEN_APPEND)
		return (3);
	if (token.type == TOKEN_HEREDOC)
		return (4);
	return (0);
}

int	check_syntax(t_shell *shell, t_command *command, t_token *token)//return because the rest is not executed
{
	int	i;

	i = 0;
	(void)command;
	(void)shell;
	while (token[i].type != TOKEN_END)
	{
		//check pipe after redir || pipe after pipe
		if ((is_redir(token[i]) && token[i + 1].type == TOKEN_PIPE) || (token[i].type == TOKEN_PIPE && token[i + 1].type == TOKEN_PIPE))
		{
			ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
			return (1);
		}
		//check pipe at the end
		if (last_token_pipe(token))
		{
			ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
			return (1);
		}
		//check redir at the end
		if (is_redir(token[i]) && token[i + 1].type == TOKEN_END)
		{
			ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
			return (1);
		}
		i++;
	}
	check_ambig_redir(command);//only if no synax error
	return (0);
}

void	check_ambig_redir(t_command *command)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	while (!command[i].end_of_cmd)
	{
		j = 0;
		//printf("checking ambiguous redirection\ntype of redirection: %i\n", command[i].redirections[j].type);
		while (command[i].redirections[j].type != TOKEN_DEFAULT)
		{
			//printf("inside loop, before if statement\n");
			//printf("condition: command[%i].redirections[%i].amb_redir: %i\n", i, j, command[i].redirections[j].amb_redir);
			if (command[i].redirections[j].amb_redir && !command[i].p_err_msg)
			{
				//printf("token[%i].value: %s\n", i, command[i].redirections[j].file);
				buffer = malloc(ft_strlen(command[i].redirections[j].file) + 50);
				my_sprintf(buffer, "minishell: %s: ambiguous redirect\n", command[i].redirections[j].file);//print once for each command
				//ft_putendl_fd(buffer, 2);//print one time for each command
				write(2, buffer, ft_strlen(buffer));
				free(buffer);
				command[i].p_err_msg = true;
				//break;
			}
			j++;
		}
		i++;
	}
}

bool	last_token_pipe(t_token *token)
{
	int	i;

	i = 0;
	while (token[i].type != TOKEN_END)
	{
		if (token[i + 1].type == TOKEN_END)
		{
			if (token[i].type == TOKEN_PIPE)
				return (true);
		}
		i++;
	}
	return (false);
}

/*
cases for check_syntax
< |: redir followed by a pipe, invalid
aismaili@c4r4p8:~$ ls > | wc
bash: syntax error near unexpected token `|'

aismaili@c4r4p8:~$ ls > "" | wc
bash: : No such file or directory
      0       0       0
assuming, that execve will take care of this, but pipe is our responibility

aismaili@c4r4p8:~$ ls > $VAR | wc	//non-existing Expansion after redir
bash: $VAR: ambiguous redirect
      0       0       0
aismaili@c4r4p8:~$ ls > $USER | wc	//existing Expansion after redir
      0       0       0

aismaili@c4r7p1:~$ ls >$VAR | ls >$VAR
bash: $VAR: ambiguous redirect
bash: $VAR: ambiguous redirect

aismaili@c4r4p8:~$ ls >>
bash: syntax error near unexpected token `newline'
aismaili@c4r4p8:~$ ls >
bash: syntax error near unexpected token `newline'




For each token in the command:
If the token is a redirection symbol (> or <):
Check if the next token is valid (not a pipe or another redirection symbol, and not an empty string).
If the next token is a variable (e.g., starts with $), check if it expands to a non-empty string.
If the token is a pipe symbol (|):
Ensure it's not the first token and that it's not immediately preceded by a redirection symbol without a valid filename.


*/

//	

/* void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->token[i].value != NULL)
	{
		printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
		i++;
	}
	printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
} */



/* int main()
{
    // Sample command string
    char str[] = "  echo   'ls' abc l\"s-\"l >>> file <file1|wc|wc-l>>file";
    t_shell shell;

	char **splited = ft_split_bash(str, " ");
   	token_simple(splited, &shell);
	printf("token_simple\n");
	print_tokens(&shell);
	
    token_adv(&shell, shell.token);
	printf("token_adv\n");
	print_tokens(&shell);
    return 0;
} */

/*
cc -o advan token_advance.c token_simple.c split_bash.c ../libft/.c -g
*/