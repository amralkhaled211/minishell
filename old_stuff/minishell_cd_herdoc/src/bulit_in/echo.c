/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:52:50 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/05 14:55:56 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static  bool    is_with_flag(char *av)
{
    int i;

    i = 0;
    if (av[i] != '-')
        return (false);
    i++;
    while (av[i]  && av[i] == 'n')
    i++;
    if (av[i] == '\0')
        return (true);
    return (false);
}

static void	print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', 1);
		i++;
	}
}

int	echo(char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	while (args[i] && is_with_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	print_args(args, n_flag, i);
	return (0);
}

/* 
#include <stdio.h>

int	main(int ac, char **av)
{
	echo(av);
	printf("newline\n");
	return	(0);
} */