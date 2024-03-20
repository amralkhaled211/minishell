/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/05 15:42:20 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	copy_value(char *new, char *value, int *j)
{
	int	k;

	k = 0;
	while (value[k])
	{
		new[*j] = value[k];
		k++;
		(*j)++;
	}
}

char	*get_value_to_str(char *old_str, char *value, int len, int ind)//protect
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (old_str[i])
	{
		if (old_str[i] == '$' && i == ind)
		{
			copy_value(new, value, &j);
			i = i + var_len(old_str + ind) + 1;
			if (old_str[i] == '\0')
				break ;
		}
		new[j++] = old_str[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*delete_and_replace(t_token *token, char *value, char *str, int ind)
{
	int		len;
	char	*new;

	errno = 0;
	len = (ft_strlen(str) - var_len(str + ind) + ft_strlen(value));
	new = get_value_to_str(str, value, len, ind);
	if (!new)
		return (NULL);
	if (token)
	{
		if (!range_quotes_two(token->value, ind))
			token->do_split = true;
		free(token->value);
		token->value = new;
		token->expanded = true;
	}
	return (new);
}

bool	range_quotes_two(char *str, int j)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	i = -1;
	in_squote = false;
	in_dquote = false;
	if (str[j] != '$')
		return (true);
	while (str[++i])
	{
		if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '$' && i == j)
		{
			if (in_squote || in_dquote)
				return (true);
		}
	}
	return (false);
}
