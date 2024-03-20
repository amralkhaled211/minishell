/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:13:09 by aismaili          #+#    #+#             */
/*   Updated: 2023/11/26 13:45:57 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

static void	checker(const char *format, va_list *args, int *ct)
{
	if (*format == 'i' || *format == 'd')
		ft_printnbr(va_arg(*args, int), ct);
	else if (*format == 'x')
		ft_printhexas(va_arg(*args, unsigned int), ct);
	else if (*format == 'X')
		ft_printhexab(va_arg(*args, unsigned int), ct);
	else if (*format == '%')
		ft_printchar('%', ct);
	else if (*format == 'c')
		ft_printchar(va_arg(*args, int), ct);
	else if (*format == 's')
		ft_printstr(va_arg(*args, char *), ct);
	else if (*format == 'p')
		ft_printaddress(va_arg(*args, void *), ct);
	else if (*format == 'u')
		ft_printunbr(va_arg(*args, unsigned int), ct);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;

	if (!format)
		return (-1);
	va_start(args, format);
	counter = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (ft_strchr("cspuidxX%", *format))
				checker(format, &args, &counter);
		}
		else
		{
			write(1, format, 1);
			counter++;
		}
		format++;
	}
	va_end(args);
	return (counter);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "Hello";
	//printf(" %p %p \n", 0, 0);
	ft_printf("€ %s %c \n", "asd", 'a');
	const char	*ab = "€";
	write(1, ab, 1);
	//ft_printf(" %p %p ", 0, 0);
	return 0;
}*/

/*
	ft_printf("This a String: %s\nThis is a Character: %c\n
	This is a Intiger: %i%%\nThis is a Hexa: %x\nThis is a HEXA: 
	%X\nThis is an Unsigned Intiger: %i\nThis is an Address: %p\n
	Bye!", s, 'a', 42, 123, -123, 123, &s);

	if (*format == 'c')
		ft_printchar(va_arg(args, int), &counter);
	else if (*format == 's')
		ft_printstr(va_arg(args, char *), &counter);
	else if (*format == 'i' || *format == 'd')
		ft_printnbr(va_arg(args, int), &counter);//in numbers
	else if (*format == 'p')
		ft_printadd(va_arg(args, void *), &counter);//in str_chr
	else if (*format == 'x')
		ft_printhexas(va_arg(args, int), &counter);//in numbers
	else if (*format == 'X')
		ft_printhexab(va_arg(args, int), &counter);//in numbers
	else if (*format == 'u')
		ft_printunbr(va_arg(args, int), &counter);//in str_chr
*/
