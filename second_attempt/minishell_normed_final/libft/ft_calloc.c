/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:13:51 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/07 15:16:16 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*p;
	size_t			total;
	unsigned char	*np;

	total = nmemb * size;
	p = malloc(total);
	if (p == NULL)
		return (NULL);
	np = (unsigned char *)p;
	while (total--)
	{
		*np = 0;
		np++;
	}
	return (p);
}
