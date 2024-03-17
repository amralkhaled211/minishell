/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:35 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 16:01:00 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	p_signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	g_exit = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	p_do_signal(void)
{
	struct sigaction	act;

	act.sa_handler = &p_signal_reset_prompt;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}

void	p_ignore_baskslash(void)//in parent ignore the signal
{
	struct sigaction	act;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGQUIT, &act, NULL);
}
