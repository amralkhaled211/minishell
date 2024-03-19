/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:20:51 by aismaili          #+#    #+#             */
/*   Updated: 2024/01/24 22:46:23 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*d;

	if (!s)
		return (NULL);
	dest = (char *)malloc(ft_strlen (s) + 1);
	if (dest == NULL)
		return (NULL);
	d = dest;
	while (*s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (d);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = "Hello World!";
	printf("%s\n", ft_strdup(s));
	free(ft_strdup(s));
	printf("%s\n", strdup(s));
	free(strdup(s));
	return (0);
}
*/
