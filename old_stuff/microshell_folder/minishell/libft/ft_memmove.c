/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 10:49:59 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/06 11:39:55 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*source;
	unsigned char	*destination;

	source = (unsigned char *)src;
	destination = (unsigned char *)dest;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (destination < source)
	{
		while (n--)
			*destination++ = *source++;
	}
	else
	{
		destination += n;
		source += n;
		while (n--)
			*(--destination) = *(--source);
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = "Hello World!";
	//char	d[50];
	//ft_memmove(s+2, s, 5);
	memmove(s+2, s, 5);
	printf("%s", s+2);
	return (0);
}
*/
