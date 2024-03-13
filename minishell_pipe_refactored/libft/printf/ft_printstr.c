/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:49:19 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/28 18:50:08 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printstr(char *s, int *ct)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_printstr("(null)", ct);
		return ;
	}
	while (s[i])
	{
		write(1, &s[i], sizeof(char));
		(*ct)++;
		i++;
	}
}
