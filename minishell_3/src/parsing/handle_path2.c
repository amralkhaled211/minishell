/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:36:46 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/19 18:03:50 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

bool	is_path(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (access(str, F_OK) != -1)
		return (true);
	/*if (str[i] == '.' && str[i + 1] == '/')
		return (true);
	if (str[i] == '/')
		return (true);
	if (str[i] == '.' && str[i + 1] == '.' && str[i + 2] == '/')
		return (true); */
	return (false);
}

char	*add_slash(char *str)
{
	char	*temp;

	temp = malloc(ft_strlen(str) + 2);
	if (!temp)
		return (NULL);
	temp[0] = '/';
	ft_memcpy(temp + 1, str, ft_strlen(str));
	temp[ft_strlen(str) + 1] = 0;
	return (temp);
}
