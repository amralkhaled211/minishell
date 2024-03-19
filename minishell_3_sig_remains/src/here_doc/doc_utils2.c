/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:24:27 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 15:31:14 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	*delete_var_for_doc(char *var, int ind)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(var) - var_len(var + ind)) + 1);
	if (!new)
		return (NULL);
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
	new[j] = '\0';
	return (new);
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	errno = 0;
	tmp = NULL;
	if (var_value == NULL)
	{
		tmp = str;
		str = delete_var_for_doc(tmp, index);
		if (!str)
			return (free(tmp), free(var_value), NULL);
		free(tmp);
	}
	else
	{
		tmp = str;
		str = delete_and_replace_for_doc(tmp, var_value, index);
		if (!str)
			return (free(tmp), free(var_value), NULL);
		free(tmp);
	}
	free(var_value);
	return (str);
}

char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	if (!name)
		return (free(number), NULL);
	free(number);
	i++;
	return (name);
}
