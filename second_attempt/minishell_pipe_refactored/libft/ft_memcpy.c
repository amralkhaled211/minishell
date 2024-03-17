/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:23:42 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/05 19:05:42 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;
	size_t			i;

	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	i = 0;
	if (src == NULL || dest == NULL)
		return (NULL);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char s[] = "Hello World!\0\0";
	char d[strlen(s)];
	ft_memcpy(d, s, 4);
	printf("%s\n", d);
	memcpy(d, s, 4);
	printf("%s", d);
	return (0);
}
*/
