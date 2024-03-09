/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:02:33 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/10 15:25:23 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static int	delete_var(t_token *token, char *var, int ind, int x)//protect
{
	int		i;
	int	 	j;
	int 	len;
	char	*new;

	i = 0;
	j = 0;
	len = ft_strlen(var) - var_len(var + ind);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return(1);
	while(var[i])
	{
		if (var[i] == '$' && i == ind)
		{
			i = i + var_len(var + ind) + 1;
			if (var[i] == '\0')
				break ;
		}
		new[j++] = var[i++];
	}
	new[j] = '\0';
	free(token[x].value);
	token[x].value = new;
	return (0);
}

int		change_var_to_val(t_token *token, char *value, int ind, int i)
{
	if(value == NULL)
	{
		if (delete_var(token, token[i].value, ind, i) == 1)
		{
			free(value);
			return (1);
		}
	}
	else
	{
		if (delete_and_replace(token, value, token[i].value, ind, i) == NULL)
		{
			free(value);
			return (1);
		}
	}
	free(value);
	return (0);
}
