/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:47:46 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/06 16:14:44 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((unsigned char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main(void)
{
	//char	*s = "Hello World!";
	//int	c = 'o';
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
	printf("%s\n", (unsigned char *)ft_memchr(tab, -1, 7));
	printf("%s", (unsigned char *)memchr(tab, -1, 7));
	return 0;
}
*/
