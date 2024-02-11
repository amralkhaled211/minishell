/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalkhal <amalkhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:34:28 by amalkhal          #+#    #+#             */
/*   Updated: 2024/02/01 13:41:08 by amalkhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../microshell.h"

void    copy_env(char **envp, t_shell *shell)
{
    int        i;
    int        d;
    char    *num;

    i = 0;
    while (envp[i])
        i++;
    shell->env = malloc(sizeof(char *) * i + 1);
    i = -1;
    while (envp[++i])
    {
        shell->env[i] = ft_strdup(envp[i]);
        if (strncmp(shell->env[i], "SHLVL", 5) == 0)//increment the SHLVL
        {
            d = ft_atoi(&shell->env[i][6]) + 1;
            num = ft_itoa(d);
            free(shell->env[i]);
            shell->env[i] = malloc(7 + ft_strlen(num));
            shell->env[i] = ft_strjoin("SHLVL=", num);
        }    
    }
    shell->env[i] = ft_strdup(envp[i]);
} */


