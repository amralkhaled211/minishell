/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aismaili <aismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:20:58 by aismaili          #+#    #+#             */
/*   Updated: 2024/03/05 16:04:23 by aismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../microshell.h"

static void	c_back_slash_exit(int signo)
{
	(void)signo;
	write(2, "Quit (cord dumped)\n", 20);
	g_exit = 131;
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	c_handle_backslash(void)//in child: exit process after SIGQUIT
{
	struct sigaction	act;

	act.sa_handler = &c_back_slash_exit;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGQUIT, &act, NULL);
}

static void	c_signal_reset_prompt(int signo)
{
	(void)signo;
	g_exit = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	c_do_signal(void)
{
	struct sigaction	act;

	act.sa_handler = &c_signal_reset_prompt;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
}
