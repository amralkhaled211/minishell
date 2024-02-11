/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:17:54 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/05 18:12:41 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	**get_the_Key_and_value_arrys(char *av)
{
	char	**arry;
	char	*equal_sign;

	equal_sign = ft_strchr(av, '=');
	arry = malloc(sizeof(char *) * (2 + 1));
	arry[0] = ft_substr(av, 0, equal_sign -  av);
	arry[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	arry[2] = NULL;
	return (arry);
}

int	export(t_shell *shell, char **av)
{
	int	i;
	char	**arry;

	i = 0;
	if(!av[i])
		return(env(shell, NULL));
	while (av[i])
	{
		if (!is_valid_var_key(av[i]))
		{
			printf("not an identifier eeee\n");
			return (1);
		}
		else if (ft_strchr(av[i], '=') != NULL)
		{
			arry = get_the_Key_and_value_arrys(av[i]);
			set_var(shell, arry[0], arry[1]);
			free_arry(arry);
		}
		i++;
	}
	return (0);
}
