/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:09:45 by amalkhal          #+#    #+#             */
/*   Updated: 2024/03/09 18:20:54 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	mini_sort(char *arr[], int n)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (i < n)
	{
		j = i;
		key = arr[i];
		while (j > 0 && ft_strcmp(arr[j - 1], key) > 0)
		{
			arr[j] = arr[j - 1];
			j = j - 1;
		}
		arr[j] = key;
		i = i + 1;
	}
}

static char	*get_value_of_var(char *env)
{
	int		i;
	int		len;
	int		start;
	char	*new;

	len = 0;
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	start = i;
	while (env[i] != '\0')
	{
		i++;
		len++;
	}
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	len = 0;
	while (env[start])
		new[len++] = env[start++];
	new[len] = '\0';
	return (new);
}

static char	*var_with_equal(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] != '=')
		i++;
	new = malloc(sizeof(char) * i + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '=';
	i++;
	new[i] = '\0';
	return (new);
}

static char	*strdup_join(char *str)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp = get_value_of_var(str);
	if (!tmp)
		return (NULL);
	tmp1 = make_qoutes(tmp);
	if (!tmp1)
		return (free(tmp), NULL);
	tmp2 = var_with_equal(str);
	if (!tmp2)
		return (free(tmp), free(tmp1), NULL);
	tmp3 = ft_strjoin(tmp2, tmp1);
	if (!tmp3)
		return (free(tmp), free(tmp1), free(tmp2), NULL);
	return (free(tmp), free(tmp1), free(tmp2), tmp3);
}

void	sort_export(t_shell *shell, char **env)
{
	int	count;
	int	i;

	count = 0;
	while (env[count] != NULL)
		count++;
	shell->export = malloc((count + 1) * sizeof(char *));
	if (!shell->export)
	{
		free_str_array(shell->env);
		exit(1);
	}
	i = -1;
	while (++i < count)
	{
		shell->export[i] = strdup_join(env[i]);
		if (!shell->export[i])
		{
			free_rest_export(shell->export, i);
			free_str_array(shell->env);
			exit (1);
		}
	}
	shell->export[count] = NULL;
	mini_sort(shell->export, count);
}
