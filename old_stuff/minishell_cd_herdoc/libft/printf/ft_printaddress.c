/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:50:27 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:55:57 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_address2(size_t add, int *ct)
{
	if (add > 15)
	{
		print_address2(add / 16, ct);
	}
	add = add % 16;
	if (add <= 9)
	{
		add = add + 48;
		write(1, &add, 1);
		(*ct)++;
	}
	else
	{
		add = add + 'a' - 10;
		write(1, &add, 1);
		(*ct)++;
	}
}

void	ft_printaddress(void *ptr, int *ct)
{
	size_t	add;

	if (ptr == 0)
	{
		ft_printstr("(nil)", ct);
		return ;
	}
	add = (size_t)ptr;
	write(1, "0x", 2);
	(*ct) += 2;
	print_address2(add, ct);
}
