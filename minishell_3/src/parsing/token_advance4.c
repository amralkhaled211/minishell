/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_advance4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:04:59 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 14:37:40 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_pos_existing(char *value, int i)//4
{
	if (i > 0 && value)
		return (true);
	return (false);
}

bool	is_cmd_arg_file_word(t_token *n_token)
{
	if ((n_token->type == TOKEN_COMMAND || n_token->type == TOKEN_ARG
			|| is_file(*n_token) || n_token->type == TOKEN_WORD))
		return (true);
	return (false);
}

bool	is_file_word_pipe(t_token *n_token)
{
	if ((is_file(*n_token) || n_token->type == TOKEN_PIPE
			|| n_token->type == TOKEN_WORD))
		return (true);
	return (false);
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
