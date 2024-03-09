/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:16:49 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/08 16:29:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_the_set(char const s1, char const *set)
{
	while (*set)
	{
		if (*set == s1)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned char	*b;
	unsigned char	*e;
	size_t			i;
	size_t			len;
	char			*trim;

	while (*s1 && in_the_set(*s1, set))
		s1++;
	b = (unsigned char *)s1;
	e = (unsigned char *)(s1 + ft_strlen(s1) - 1);
	while (e >= b && in_the_set(*e, set))
		e--;
	len = e - b + 1;
	trim = malloc((len + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trim[i] = b[i];
		i++;
	}
	trim[len] = 0;
	return (trim);
}
/*
#include <stdio.h>

int	main(void)
{
	char const s1[] = "1Alireza123";
	char const set[] = "3ez21rfda";
	char *trimmed = ft_strtrim(s1, set);
	if (trimmed != NULL)
	{
		printf("%s\n", trimmed);
        	free(trimmed);
        }
        else
        	printf("Memory allocation failed\n");
	return 0;
}
*/
