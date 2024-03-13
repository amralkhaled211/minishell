/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_simple2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:41:38 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/07 15:01:00 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	assign_type(t_shell *shell, char *keyword, t_e_types type, int i)
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
		perror("ft_strdup fail");
		free_after_malloc_fail(shell, i, 1);
	}
}

bool	identify_type_sim(t_shell *shell, char *keyword, t_token *token, int i)
{
	(void)token;
	if (keyword == NULL)
		return (assign_type(shell, keyword, TOKEN_END, i), true);
	else if (!ft_strncmp(keyword, "|", ft_strlen(keyword)))
		return (assign_type(shell, keyword, TOKEN_PIPE, i), true);
	else if (!ft_strncmp(keyword, ">", ft_strlen(keyword)))
		return (assign_type(shell, keyword, TOKEN_REDIRECT_OUT, i), true);
	else if (!ft_strncmp(keyword, "<", ft_strlen(keyword)))
		return (assign_type(shell, keyword, TOKEN_REDIRECT_IN, i), true);
	else if (!ft_strncmp(keyword, ">>", ft_strlen(keyword)))
		return (assign_type(shell, keyword, TOKEN_APPEND, i), true);
	else if (!ft_strncmp(keyword, "<<", ft_strlen(keyword)))
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
