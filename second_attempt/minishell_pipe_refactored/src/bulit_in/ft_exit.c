/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:43:17 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/14 12:03:29 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

int	ft_exit(t_shell *shell, char **args)
{
	int		i;

	i = 0;
	if (!args[i])
		free_before_exit(shell);
	else if (num_of_args(args) > 1)
		plural_args(shell, args);
	else if (num_of_args(args) == 1)
	{
		if (is_numeric(shell, args[i]))
			single_arg(shell, args);
		else
			single_arg_sec(shell, args);
	}
	return (0);
}

void	plural_args(t_shell *shell, char **args)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(ft_strlen(args[i]) + 45);
	if (!buffer)
		free_after_malloc_fail(shell, -1, 5);
	if (is_numeric(shell, args[i]))
	{
		my_sprintf(buffer, "minishell: %s: too many arguments\n", "exit");
		shell->exit_status = 1;
	}
	else
	{
		my_sprintf(buffer, "minishell: exit: %s: numeric argument required\n",
			args[i]);
		shell->exit_status = 2;
	}
	//write(2, "exit\n", 5);
	write (2, buffer, ft_strlen(buffer));
	free(buffer);
	free_before_exit(shell);
}

void	single_arg(t_shell *shell, char **args)
{
	int		i;
	char	*converted;
	char	*original;

	i = 0;
	original = ft_strtrim(args[i], " +");
	if (!original)
		free_after_malloc_fail(shell, -1, 4);
	//write(2, "exit\n", 5);
	shell->exit_status = ft_atoi(args[i]);
	converted = ft_itoa(shell->exit_status);
	cmp_orig_conv(shell, args, original, converted);
	free(original);
	free(converted);
	free_before_exit(shell);
}

void	cmp_orig_conv(t_shell *shell, char **args, char *original,
					char *converted)
{
	int		i;
	char	*adj_original;
	char	*adj_converted;
	char	*buffer;

	adj_original = rm_zero(original);
	adj_converted = rm_zero(converted);
	i = 0;
	if (ft_strcmp(adj_converted, adj_original))
	{
		buffer = malloc(ft_strlen(args[i]) + 55);
		my_sprintf(buffer, "minishell: exit: %s: numeric argument required\n",
			args[i]);
		write(2, buffer, ft_strlen(buffer));
		free(buffer);
		free(original);
		free(converted);
		shell->exit_status = 2;
		free_before_exit(shell);
	}
}

void	single_arg_sec(t_shell *shell, char **args)
{
	char	*buffer;
	int		i;

	i = 0;
	buffer = malloc(ft_strlen(args[i]) + 55);
	if (!buffer)
		free_after_malloc_fail(shell, -1, 5);
	my_sprintf(buffer, "minishell: exit: %s: numeric argument required\n",
		args[i]);
	write(2, buffer, ft_strlen(buffer));
	free(buffer);
	shell->exit_status = 2;
	free_before_exit(shell);
}
