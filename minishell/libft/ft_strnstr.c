/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:41:49 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/06 18:24:54 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0' || little == NULL)
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (little[j] == big[i])
		{
			while (little[j] == big[i + j] && i + j < len)
			{
				if (little[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char	str[] = "lorem ipsum dolor sit amet";
	char	to_find[] = "sit";

	printf("%s\n", ft_strnstr(str, to_find, 2));
	return (0);
}
*/