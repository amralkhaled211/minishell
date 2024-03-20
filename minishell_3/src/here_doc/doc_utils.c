/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:22:27 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/17 14:16:58 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*ft_strjoin_doc(char *s1, char *s2, int spaces)
{
	char				*new_str;
	unsigned int		i;
	unsigned int		j;

	i = 0;
	j = -1;
	if (s1 == NULL)
		return (NULL);
	new_str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + spaces + 1));
	if (new_str == NULL)
		return (free(s1), NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[++j] != '\0')
		new_str[i + j] = s2[j];
	while (spaces-- > 1)
		new_str[i + j++] = ' ';
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

static char	*create_initial_str(char **tab)
{
	char	*str;

	errno = 0;
	str = ft_strdup(tab[0]);
	if (!str && errno != 0)
		return (NULL);
	return (str);
}

static char	*concatenate_strings(char *base, char *append)
{
	char	*result;

	result = ft_strjoin_doc(base, append, 0);
	if (!result)
		return (NULL);
	return (result);
}

static char	*add_initial_spaces(int spaces, char *base)
{
	char	*result;

	result = add_spaces(spaces, base);
	if (!result)
		return (NULL);
	return (result);
}

char	*make_str_from_tab(char **tab, char *line)
{
	char	*str;
	int		i;
	int		spac;
	int		spac2;

	i = -1;
	str = NULL;
	spac2 = count_first_spaces(line);
	while (tab[++i])
	{
		spac = count_spaces(line);
		if (i == 0)
			str = create_initial_str(tab);
		else
			str = concatenate_strings(str, tab[i]);
		if (!str)
			return (free(line), free_str_array(tab), NULL);
		if (tab[i + 1])
			str = ft_strjoin_doc(str, " ", spac);
		if (!str)
			return (free(line), free_str_array(tab), NULL);
	}
	if (spac2 != 0)
		str = add_initial_spaces(spac2, str);
	return (free(line), free_str_array(tab), str);
}
