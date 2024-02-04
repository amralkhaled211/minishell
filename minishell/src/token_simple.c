/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:54 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/02 16:25:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	assign_type(t_shell *shell, char *keyword, e_types type, int i)
{
	shell->token[i].type = type;
	if (!keyword)
	{
		shell->token[i].value = keyword;
		return ;
	}
	shell->token[i].value = ft_strdup(keyword);
	if (!shell->token[i].value)
	{
		//free array all token->value, free allocated ones only, splited (2D Array) from main
		perror("ft_strdup fail");
		free_after_malloc_fail(shell, i, 1);
	}
}

bool	identify_type_sim(t_shell *shell, char *keyword, t_token *token, int i)//Pipes and Redirections
{
	(void)token;
	if (keyword == NULL)
		return (assign_type(shell, keyword, TOKEN_END, i), true);
	else if (!ft_strncmp(keyword, "|", ft_strlen(keyword)))//end of cmd / begin of new cmd
		return (assign_type(shell, keyword, TOKEN_PIPE, i), true);
	else if (!ft_strncmp(keyword, ">", ft_strlen(keyword)))//outfile: output will be redirected to the following file; delete existing content in file/overwrite it
		return (assign_type(shell, keyword, TOKEN_REDIRECT_OUT, i), true);
	else if (!ft_strncmp(keyword, "<", ft_strlen(keyword)))//infile: input will be read from the following file
		return (assign_type(shell, keyword, TOKEN_REDIRECT_IN, i), true);
	else if (!ft_strncmp(keyword, ">>", ft_strlen(keyword)))//append: do not delete existing content in outfile, but add to it
		return (assign_type(shell, keyword, TOKEN_APPEND, i), true);
	else if (!ft_strncmp(keyword, "<<", ft_strlen(keyword)))//heredoc: a delimiter will follow directly with or without any space in between
		return (assign_type(shell, keyword, TOKEN_HEREDOC, i), true);
	return (false);
}

void	analyze_result(char **input, t_shell *shell, int i)
{
	if (identify_type_sim(shell, input[i], &shell->token[i], i))
		return ;
	else
		assign_type(shell, input[i], TOKEN_WORD, i);
}

int	token_simple(char **result, t_shell *shell)
{
	int	i;

	i = 0;
	while (result[i])
	{
		analyze_result(result, shell, i);
		i++;
	}
	analyze_result(result, shell, i);
	if (shell->token[0].type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (2);
	}
	i = 0;
	while (result[i])
	{
		printf("++++in token_simple\n++++result[%i]: %s\n", i, result[i]);
		if (!is_closed_quote(result[i]))
		{
			ft_putendl_fd("minishell: warning: unclosed quotes", 2);
			return (3);
		}
		i++;
	}
	return (0);
}

bool	is_closed_quote(char *str)//syntax error check
{
	int		i;
	bool	in_quote;
	char	quote;

	quote = '\0';
	i = 0;
	in_quote = false;
	while (str[i])
	{
		//case: abc "hell'o wor'ld" def "df"dkf"dsf"dsaf
		if (is_quote(str[i]) && (!in_quote || quote == str[i]))
		{
			in_quote = !in_quote;
			if (in_quote)
				quote = str[i];
			else
				quote = '\0';
		}
		i++;
	}
	return (!in_quote);
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
	printf("i %d: Type = %d, Value = %s\n", i, shell->token[i].type, shell->token[i].value);
}

int	main(void)
{
	t_shell	shell;

	char *input = readline("parseshell $ ");
	char **splited = ft_split_bash(input, " \t");
	token_simple(splited, &shell);
	print_tokens(&shell);
} */
