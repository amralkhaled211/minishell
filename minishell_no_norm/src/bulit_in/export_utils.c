/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:40:25 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/08 15:42:26 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	**get_the_key_and_value_arrys(char *av)
{
	char	**arry;
	char	*equal_sign;

	equal_sign = ft_strchr(av, '=');
	arry = malloc(sizeof(char *) * (2 + 1));
	if (!arry)
		return (NULL);
	arry[0] = ft_substr(av, 0, equal_sign - av);
	if (!arry[0])
		return (free(arry), NULL);
	arry[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	if (!arry[1])
		return (free(arry[0]), free(arry), NULL);
	arry[2] = NULL;
	return (arry);
}

void	help_export(t_shell *shell, char *av, char **arry)
{
	arry = get_the_key_and_value_arrys(av);
	if (!arry)
		free_after_malloc_fail(shell, -1, 5);
	if (set_var(shell, arry[0], arry[1]) != 0)
	{
		free_arry(arry);
		free_after_malloc_fail(shell, -1, 5);
	}
	if (set_export_var_with_value(shell, arry[0], arry[1]) == -1)
	{
		free_arry(arry);
		free_after_malloc_fail(shell, -1, 5);
	}
	free_arry(arry);
}
