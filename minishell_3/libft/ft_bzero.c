/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 17:01:30 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/05 18:22:25 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>

int	main(void)
{
	int	i = 0;
	char	s[] = "Hello World!";
	int	l = strlen(s);
	ft_bzero(s, 3);

	//bzero(s, 3);
	printf("%s", s);
	while (i < l)
	{
		printf("%c", s[i]);
		i++;
	}
	return (0);
}*/
