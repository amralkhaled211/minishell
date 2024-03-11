/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:51:39 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:51:51 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printhexab(unsigned int hd, int *ct)
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
		ft_printhexab(h / 16, ct);
	h = h % 16;
	if (h <= 9)
	{
		h = h + 48;
		write(1, &h, 1);
		(*ct)++;
	}
	else
	{
		h = h + 65 - 10;
		write(1, &h, 1);
		(*ct)++;
	}
}
