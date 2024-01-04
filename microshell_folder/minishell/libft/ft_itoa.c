/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:16:58 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/11 17:19:52 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_num(char *str, long long n, int i)
{
	long long	temp;
	int			term;

	temp = n;
	term = i + 1;
	if (temp < 0)
		temp = -temp;
	while (i >= 0)
	{
		str[i] = '0' + temp % 10;
		temp /= 10;
		i--;
		if (n < 0)
			str[0] = '-';
	}
	str[term] = 0;
	return (str);
}

char	*ft_itoa(int n)
{
	long long	temp;
	int			len;
	char		*str;

	temp = n;
	len = 0;
	while (temp != 0)
	{
		if (temp < 0)
		{
			len++;
			temp = -temp;
		}
		temp /= 10;
		len++;
	}
	if (n == 0)
		len = 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str = ft_fill_num(str, n, len - 1);
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i = -2147483648;
	
	printf("%s", ft_itoa(i));
	free(ft_itoa(i));
	return (0);
}
*/
