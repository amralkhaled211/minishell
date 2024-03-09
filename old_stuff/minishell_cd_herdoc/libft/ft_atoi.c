/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:28:10 by aismaili          #+#    #+#             */
/*   Updated: 2023/12/14 22:58:27 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *nptr)
{
	int		sign;
	long	result;
	int		digit;

	sign = 1;
	result = 0;
	while (*nptr && (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r')))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr == '0')
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		digit = *nptr - '0';
		result = result * 10 + digit;
		nptr++;
	}
	return (sign * result);
}
/*
#include <stdio.h>

int main(void)
{
    char input[] = "+0000000000000000000000000000000000000000000000000000123";
    int value = ft_atoi(input);
    printf("%d\n", value);
    return 0;
}
*/