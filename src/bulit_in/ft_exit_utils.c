/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:48:57 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 18:14:24 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

char	*rm_zero(char *original)
{
	if (*original == '-')
		original++;
	while (*original == '0')
		original++;
	return (original);
}

bool	is_numeric(t_shell *shell, char *arg)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strtrim(arg, " ");
	if (!tmp)
		free_after_malloc_fail(shell, -1, 5);
	if (tmp && !tmp[i])
		return (free(tmp), false);
	while (tmp && tmp[i])
	{
		if (i == 0 && (tmp[i] == '+' || tmp[i] == '-'))
			i++;
		if (!ft_isdigit(tmp[i]))
			return (free(tmp), false);
		i++;
	}
	return (free(tmp), true);
}

int	num_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
