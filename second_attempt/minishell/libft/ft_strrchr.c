/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:36:29 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/06 13:45:47 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	if ((char)c == 0)
		return ((char *)&s[ft_strlen(s)]);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = "Hello Hey!";
	int	c = 'e';
	printf("%s\n", ft_strrchr(s, c));
	char	*result = ft_strrchr(s, c);
	if (result != NULL)
	{
		printf("%s\n%p\n%c\n%p\n", *result, result, s[7], &s[7]);
	}
	return 0;
}*/
