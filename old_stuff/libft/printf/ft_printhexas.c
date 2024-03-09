/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexas.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:08:07 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:47:49 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printhexas(unsigned int hd, int *ct)
{
	long int	h;

	h = hd;
	if (h < 0)
	{
		write(1, "-", 1);
		(*ct)++;
		h = -h;
	}
	if (h > 15)
		ft_printhexas(h / 16, ct);
	h = h % 16;
	if (h <= 9)
	{
		h = h + 48;
		write(1, &h, 1);
		(*ct)++;
	}
	else
	{
		h = h + 97 - 10;
		write(1, &h, 1);
		(*ct)++;
	}
}
