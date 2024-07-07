/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:26:52 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/27 18:26:54 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

void	quote_removal(t_shell *shell, t_token *token)
{
	int		i;
	char	*temp;

	i = 0;
	(void)shell;
	while (token[i].type != TOKEN_END)
	{
		if (token[i].expanded)
		{
			i++;
			continue ;
		}
		if (with_quote(token[i].value))
			token[i].with_quote = true;
		errno = 0;
		temp = handle_quotes(shell, token[i].value, 2);
		free(token[i].value);
		token[i].value = temp;
		i++;
	}
}
