/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:22:40 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/08 20:12:48 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlengnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchrgnl(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (&s[ft_strlengnl(s)]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*ns;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	ns = (char *)malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!ns)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		ns[i] = s1[i];
	while (s2[j])
		ns[i++] = s2[j++];
	ns[ft_strlengnl(s1) + ft_strlengnl(s2)] = '\0';
	return (free(s1), ns);
}
