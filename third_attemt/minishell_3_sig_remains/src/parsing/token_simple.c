/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:10:54 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/17 18:20:37 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	array_len(char **result)
{
	int	num;

	num = 0;
	while (result[num])
		num++;
	return (num);
}

void	default_token(t_token *token, int num)
{
	int	i;

	i = -1;
	while (++i <= num)
	{
		token[i].value = NULL;
		token[i].type = TOKEN_DEFAULT;
		token[i].amb_redir = false;
		token[i].do_split = false;
		token[i].last_token = false;
		token[i].expanded = false;
		token[i].var_splited = NULL;
	}
}

int	token_simple(char **result, t_shell *shell)
{
	int	i;

	i = -1;
	shell->num_tokens = array_len(result);
	shell->token = malloc(sizeof(t_token) * (shell->num_tokens + 2));
	if (!shell->token)
		free_after_malloc_fail(shell, -1, 1);
	default_token(shell->token, shell->num_tokens + 1);
	while (result[++i])
		analyze_result(result, shell, i);
	analyze_result(result, shell, i);
	return (f_syntax_check(shell, result));
}

int	f_syntax_check(t_shell *shell, char **result)
{
	int	i;

	i = 0;
	if (shell->token[0].type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		shell->exit_status = 2;
		return (2);
	}
	while (result[i])
	{
		if (!is_closed_quote(result[i]))
		{
			ft_putendl_fd("minishell: warning: unclosed quotes", 2);
			shell->exit_status = 2;
			return (3);
		}
		i++;
	}
	return (0);
}

bool	is_closed_quote(char *str)
{
	int		i;
	bool	in_quote;
	char	quote;

	quote = '\0';
	i = 0;
	in_quote = false;
	while (str[i])
	{
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
