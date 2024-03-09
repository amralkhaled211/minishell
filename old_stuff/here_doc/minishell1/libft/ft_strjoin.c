/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:48:51 by aismaili          #+#    #+#             */
/*   Updated: 2024/02/02 10:44:01 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rns;
	char	*ns;

	ns = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ns == NULL)
		return (NULL);
	rns = ns;
	while (*s1)
	{
		*ns = *s1;
		ns++;
		s1++;
	}
	while (*s2)
	{
		*ns = *s2;
		ns++;
		s2++;
	}
	*ns = 0;
	return (rns);
}
/*
#include <stdio.h>

int	main(void)
{
	char s[] = "HELLO WORLD!";
	char a[] = "BYE BYE";
	char	*result = ft_strjoin(s, a);
	printf("%s", result);
	free(result);
}
*/
