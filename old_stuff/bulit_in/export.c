/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:17:54 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/01 18:26:20 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static char	**get_the_Key_and_value_arrys(char *av)
{
	char	**arry;
	char	*equal_sign;

	equal_sign = ft_strchr(av, '=');
	arry = malloc(sizeof(char *) * (2 + 1));
	if (!arry)
		return (NULL);
	arry[0] = ft_substr(av, 0, equal_sign -  av);
	if (!arry[0])
		return (free(arry), NULL);
	arry[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	if (!arry[1])
		return (free(arry[0]), free(arry), NULL);
	arry[2] = NULL;
	return (arry);
}

static int export_env(t_shell *shell)
{
	int i;

	i = 0;
	if (!shell->export)
	{
		return (1);
	}
	while (shell->export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(shell->export[i++], 1);
	}
	return(0);
}

int	export(t_shell *shell, char **av)
{
	int		i;
	int		tmp;
	char	**arry;

	i = 0;
	arry = NULL;
	if(!av[i])
		return(export_env(shell));
	while (av[i])
	{
		if (!is_valid_var_key(av[i]))
			return (cmd_printf("export", av[i], " not a valid identifier", 1));
		else if (ft_strchr(av[i], '=') == NULL)
		{
			tmp = get_export_var_ind(shell->export, av[i]);//this is fine
			if (tmp == -2)
				free_after_malloc_fail(shell, -1, 5);
			if (tmp == -1)
			{
				if (set_export_var_no_value(shell, av[i++]) == true)//this is fine
					continue;
			}
		}
		else if (ft_strchr(av[i], '=') != NULL)
			help_export(shell, av[i], arry);
		i++;
	}
	return (0);
}

void	help_export(t_shell *shell, char *av, char **arry)
{
	arry = get_the_Key_and_value_arrys(av);
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
