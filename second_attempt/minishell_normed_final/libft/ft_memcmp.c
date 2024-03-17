/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:21:14 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/06 16:40:11 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] > str2[i] || str1[i] < str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s1[] = "Hello World";
	char	s2[] = "Hello Warld";
	printf("%i\n", ft_memcmp(s1, s2, 20));
	printf("%i", memcmp(s1, s2, 20));
	return 0;
}
*/
