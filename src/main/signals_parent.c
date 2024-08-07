/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:35 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/28 12:47:39 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	handler_p(int status)
{
	if (status == SIGINT)
	{
		g_exit = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	p_do_signal(void)
{
	signal(SIGINT, &handler_p);
	signal(SIGQUIT, SIG_IGN);
}
