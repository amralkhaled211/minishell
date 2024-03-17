/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:52:19 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:52:23 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printunbr(unsigned int n, int *ct)
{
	unsigned long int	nb;

	nb = n;
	if (nb > 9)
	{
		ft_printunbr(nb / 10, ct);
	}
	nb = nb % 10;
	nb = nb + 48;
	write(1, &nb, 1);
	(*ct)++;
}
