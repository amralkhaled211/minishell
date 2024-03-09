/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:54 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/24 22:48:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	assign_type(char *keyword, t_token *token, e_types type)
{
	token->type = type;
	token->value = ft_strdup(keyword);
}

bool	identify_type_sim(char *keyword, t_token *token)//Pipes and Redirections
{
	int	i;

	i = 0;
	if (!ft_strncmp(keyword, "|", ft_strlen(keyword)))//end of cmd / begin of new cmd
		return (assign_type(keyword, token, TOKEN_PIPE), true);
	else if (!ft_strncmp(keyword, ">", ft_strlen(keyword)))//outfile: output will be redirected to the following file; delete existing content in file/overwrite it
		return (assign_type(keyword, token, TOKEN_REDIRECT_OUT), true);
	else if (!ft_strncmp(keyword, "<", ft_strlen(keyword)))//infile: input will be read from the following file
		return (assign_type(keyword, token, TOKEN_REDIRECT_IN), true);
	else if (!ft_strncmp(keyword, ">>", ft_strlen(keyword)))//append: do not delete existing content in outfile, but add to it
		return (assign_type(keyword, token, TOKEN_APPEND), true);
	else if (!ft_strncmp(keyword, "<<", ft_strlen(keyword)))//heredoc: a delimiter will follow directly with or without any space in between
		return (assign_type(keyword, token, TOKEN_HEREDOC), true);
	else if (keyword == NULL)
		return (assign_type(keyword, token, TOKEN_END), true);
	return (false);
}

void	analyze_result(char **input, t_shell *shell, int i)
{
	if (identify_type_sim(input[i], &shell->token[i]))
		return ;
	else
		assign_type(input[i], &shell->token[i], TOKEN_WORD);
}

void	token_simple(char **result, t_shell *shell)
{
	int	i;

	i = 0;
	while (result[i])
	{
		analyze_result(result, shell, i);
		i++;
	}
	analyze_result(result, shell, i);
}

/* void	print_tokens(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->token[i].value)
	{
		printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
		i++;
	}
} */

/* int	main(void)
{
	t_shell	shell;

	char *input = readline("parseshell $ ");
	char **splited = ft_split_bash(input, " \t");
	token_simple(splited, &shell);
	//print_tokens(&shell);
} */
