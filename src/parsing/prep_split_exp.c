/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_split_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:35:13 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 19:40:45 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	assign_exp_pos1(t_token *token, t_index *i)
{
	char	*tmp;
	int		found;

	found = 0;
	if (exp_in_quote(token->orig_input, i->a))
		token->exp_pos[i->c + 1].in_quote = true;
	if (token->array_exp[++i->b])
	{
		found = 1;
		token->exp_pos[++i->c].start = i->d;
		token->exp_pos[i->c].end = i->d + ft_strlen(token->array_exp[i->b]) - 1;
		i->d = i->d + ft_strlen(token->array_exp[i->b]) - 1;
		tmp = get_var_only(token->orig_input + i->a + 1);
		if (!tmp)
			return (-1);
		i->a += ft_strlen(tmp);
		free(tmp);
	}
	return (found);
}

int	assign_exp_pos2(t_token *token, t_index *i)
{
	char	*tmp;

	token->exp_pos[++i->c].unset = true;
	token->exp_pos[i->c].start = i->d;
	token->exp_pos[i->c].end = i->d;
	i->d--;
	tmp = get_var_only(token->orig_input + i->a + 1);
	if (!tmp)
		return (-1);
	i->a += ft_strlen(tmp);
	free(tmp);
	return (0);
}

static void	init_for_prep_exp_var(t_shell *shell, t_token *token, t_index *i)
{
	i->a = 0;
	i->b = -1;
	i->c = -1;
	i->d = 0;
	token->exp_pos = malloc(sizeof(t_exp_pos) * (token->j + 1));
	if (!token->exp_pos)
		free_after_malloc_fail(shell, -1, 2);
	default_exp_pos(token);
}

static int	prep_exp_var(t_shell *shell, t_token *token)
{
	t_index	i;
	int		found;

	init_for_prep_exp_var(shell, token, &i);
	while (token->orig_input[i.a])
	{
		if (token->orig_input[i.a] == '$'
			&& is_spertor(token->orig_input[i.a + 1]) == false
			&& range_quotes(token->orig_input, i.a) == false
			&& inside_dquote(shell, token->orig_input, i.a) == false)
		{
			found = assign_exp_pos1(token, &i);
			if (found == -1)
				return (-1);
			else if (found == 0)
				if (assign_exp_pos2(token, &i) == -1)
					return (-1);
		}
		i.a++;
		i.d++;
	}
	return (0);
}

void	token_split_exp(t_shell *shell, t_token *token)
{
	int		i;

	i = 0;
	while (token[i].type != TOKEN_END)
	{
		if (token[i].do_split)
		{
			errno = 0;
			if (prep_exp_var(shell, &token[i]) == -1)
				free_after_malloc_fail(shell, -1, 2);
			token[i].var_splited = ft_split_sec(&token[i],
					token[i].value, " \t");
			if (!token[i].var_splited && errno != 0)
				free_after_malloc_fail(shell, -1, 2);
		}
		i++;
	}
}
