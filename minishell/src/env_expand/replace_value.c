/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:38:14 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/03 19:06:42 by aismaili         ###   ########.fr       */
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

static char	*get_value_to_str(char *old_str, char *value, int len, int ind)
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
				break;
		}
		new[j++] = old_str[i++];
	}
	new[j] = '\0';
	return (new);
}

char	*delete_and_replace(t_token *token, char *value, char *str, int ind, int i)
{
	int	len;
	char *new;

	len = (ft_strlen(value) - var_len(value + ind) + ft_strlen(str));
	new = get_value_to_str(str, value, len, ind);//
	//printf("in DELETE and REPLACE: \nstr: %s\nvalue: %s\nnew: %s\nind: %i\nlen: %i\n", str, value, new, ind, len);
	if (token)
	{
		free(token[i].value);
		token[i].value = new;
	}
	return (new);
}