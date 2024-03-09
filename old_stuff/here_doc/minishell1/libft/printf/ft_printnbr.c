/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:48:11 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:48:27 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printnbr(int n, int *ct)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		(*ct)++;
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_printnbr(nb / 10, ct);
	}
	nb = nb % 10;
	nb = nb + 48;
	write(1, &nb, 1);
	(*ct)++;
}
