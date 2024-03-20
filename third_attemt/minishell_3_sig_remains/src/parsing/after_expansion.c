/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:14:56 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/19 15:49:42 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	token_after_expansion(t_shell *shell, t_token *token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	token_split_exp(shell, token);
	shell->num_tokens = get_size_n_token(token, shell->num_tokens);
	shell->n_token = malloc(sizeof(t_token) * (shell->num_tokens + 2));
	if (!shell->n_token)
		free_after_malloc_fail(shell, -1, 2);
	default_token(shell->n_token, shell->num_tokens + 1);
	while (token[i].type != TOKEN_END)
	{
		if (token[i].do_split == false)
		{
			if (copy_token(&shell->n_token[j], &token[i]) == -1)
				free_after_malloc_fail(shell, j, 3);
		}
		else if (token[i].do_split == true)
			j = add_tokens(shell, shell->n_token, &token[i], j);
		i++;
		j++;
	}
	copy_token(&shell->n_token[j], &token[i]);
}

int	add_tokens(t_shell *shell, t_token *n_token, t_token *token, int j)
{
	int	k;

	k = -1;
	while (token->var_splited && token->var_splited[++k])
	{
		n_token[j].amb_redir = false;
		n_token[j].do_split = false;
		n_token[j].expanded = true;
		n_token[j].type = TOKEN_WORD;
		errno = 0;
		n_token[j].value = ft_strdup(token->var_splited[k]);
		if (!n_token[j].value && errno != 0)
			free_after_malloc_fail(shell, j, 3);
		n_token[j].var_splited = NULL;
		j++;
	}
	j--;
	return (j);
}

int	copy_token(t_token *n_token, t_token *token)
{
	n_token->amb_redir = token->amb_redir;
	n_token->do_split = token->do_split;
	n_token->type = token->type;
	n_token->expanded = token->expanded;
	errno = 0;
	n_token->value = ft_strdup(token->value);
	if (!n_token->value && errno != 0)
		return (-1);
	n_token->var_splited = token->var_splited;
	return (0);
}

int	get_size_n_token(t_token *token, int num_tokens)
{
	int		i;
	int		size;

	i = 0;
	size = num_tokens;
	while (token[i].type != TOKEN_END)// && token[i].type != TOKEN_DEFAULT
	{
		if (token[i].do_split)
			size += get_size_str_array(token[i].var_splited);
		i++;
	}
	return (size);
}

void	token_split_exp(t_shell *shell, t_token *token)
{
	int		i;

	i = 0;
	while (token[i].type != TOKEN_END)//&& token[i].type != TOKEN_DEFAULT
	{
		if (token[i].do_split)
		{
			errno = 0;
			token[i].var_splited = ft_split_sec(token[i].value, " \t");
			if (!token[i].var_splited && errno != 0)
				free_after_malloc_fail(shell, -1, 2);
		}
		i++;
	}
}
