/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:41:00 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/05 16:44:09 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static bool    delete_var(t_shell *shell, int ind)
{
    int i;
    int count;

    if (ind > get_var_count(shell->env))
        return(false);
    free(shell->env[ind]);
    i = ind;
    count = ind;
    while(shell->env[i + 1])
    {
        shell->env[i] = ft_strdup(shell->env[i + 1]);
        free(shell->env[i + 1]);
        count++;
        i++;
    }
    shell->env = realloc_env_var(shell, count);
    if (!shell->env)
        return(false);
    return(true);
}

int unset(t_shell *shell, char **args)
{
    int i;
    int ind;

    i = 0;
    while (args[i])
    {
        if(!is_valid_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
        {
            printf("invalid identifier\n");
            return (1);
        }
        else
        {
            ind = get_var_ind(shell->env, args[i]);
            if (ind != -1)
                delete_var(shell, ind);
        }
        i++;
    }
    return (0);
}
