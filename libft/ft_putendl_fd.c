/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:22:18 by aismaili          #+#    #+#             */
/*   Updated: 2023/09/12 17:27:29 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], sizeof(char));
		i++;
	}
	write(fd, "\n", sizeof(char));
}
/*
int	main(void)
{
	ft_putendl_fd("abcd", 1);
	return 0;
}
*/
