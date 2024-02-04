#include "microshell.h"

//command: ls -l | wc > out.txt

void	parsing(char **splited)
{
	int			i;
	int			j;
	t_command	*tokens;

	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_command));
	//devide into diff tokens
	while (splited[i])
	{
		if (is_command)
			tokens->cmd = splited[i];
		else if (is_arument(splited[i]))
			tokens->args[j++] = splited[i];
		else if ()
	}
	
}

bool	is_command(char *token)
{

}

bool	is_argument(char *token)
{

}


char	**ft_define()
{
	//
}




	//devide into diff commands, dictate order (precedence)
	//ft_define()
	//is it builtin or external
		//if not builtin use of execve
		//else use of our builtin functions


	//execution
		//check for builtin
		/* if (is_builtin(splited[i]))
		{
		}
//iterate through the commands and cmp to builtins
bool	is_builtin(char *token)
{
	//straight forward: cmp to builtin and return true or false
	//create an array of char *, filled with the builtins
	//if (ft_strncmp(token, builtin[i++], ft_strlen(token))) in a while loop
}
		*/

/*
                [Logical AND]
                 /         \
                /           \
          [Pipeline]      [Command]
           /       \         |
          /         \        |
     [Command]   [Command] [Argument]
       /  \        /  \       |
      /    \      /    \      |
 [Argument] [Argument] [Argument] [Argument]


*/