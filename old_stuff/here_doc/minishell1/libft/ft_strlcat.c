/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:28:30 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/07 13:30:32 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dest_len;
	size_t			i;

	dest_len = 0;
	i = 0;
	while (dst[dest_len] && dest_len < size)
		dest_len++;
	while (src[i] && (dest_len + i + 1) < size)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if (dest_len < size)
		dst[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[] = "Hello World";
	char	src [] = "lorem ipsum dolor sit amet";
	printf ("%zu\n", ft_strlcat(dest, src, 30));
	printf("%s", dest);
	return (0);
}
*/
