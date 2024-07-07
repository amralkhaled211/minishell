/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:02:33 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/27 18:29:49 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	delete_var(t_token *token, char *var, int ind, int x)
{
	int		len;
	char	*new;

	len = ft_strlen(var) - var_len(var + ind);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (1);
	new = mini_delete_var(var, new, ind);
	free(token[x].value);
	token[x].value = new;
	return (0);
}

char	*mini_delete_var(char *var, char *new, int ind)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '$' && i == ind)
		{
			i = i + var_len(var + ind) + 1;
			if (var[i] == '\0')
				break ;
		}
		new[j++] = var[i++];
	}
	if (j > 0)
		new[j] = '\0';
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}

static int	count_dollar(char *orig_input)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	if (!orig_input)
		return (0);
	while (orig_input[++i])
	{
		if (orig_input[i] == '$')
			count++;
	}
	return (count);
}

int	change_var_to_val(t_token *token, char *value, int ind, int i)
{
	if (value == NULL && errno != 0)
	{
		return (1);
	}
	if (token[i].j == -1)
	{
		token[i].array_exp = malloc(sizeof(char *)
				* (count_dollar(token[i].orig_input) + 1));
		if (!token[i].array_exp)
			return (free(value), 1);
	}
	token[i].array_exp[++token[i].j] = ft_strdup(value);
	if (!token[i].array_exp[token[i].j] && errno != 0)
		return (free(value), 1);
	token[i].array_exp[token[i].j + 1] = NULL;
	if (value == NULL)
	{
		if (delete_var(token, token[i].value, ind, i) == 1)
			return (free(value), 1);
	}
	else
		if (delete_and_replace(&token[i], value, token[i].value, ind) == NULL)
			return (free(value), 1);
	return (free(value), 0);
}
