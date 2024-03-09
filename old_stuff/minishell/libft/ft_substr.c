/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:02:39 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/08 15:48:07 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	size_t			b;
	unsigned char	*sub;

	i = 0;
	b = 0;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start > ft_strlen(s))
		len = 0;
	sub = malloc(((len + 1) * sizeof(char)));
	if (sub == NULL)
		return (NULL);
	while (s[i])
	{
		if (i >= start && b < len)
			sub[b++] = s[i];
		i++;
	}
	sub[b] = '\0';
	return ((char *)sub);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_substr("hola", 0, 1844674407));
}
*/
