/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:20:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 11:15:33 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	handler_c(int status)
{
	if (status == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	c_do_signal(void)
{
	signal(SIGINT, &handler_c);
	signal(SIGQUIT, SIG_IGN);
}
