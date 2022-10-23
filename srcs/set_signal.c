/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:44:14 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 16:38:23 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 1);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_b(int signal)
{
	if (signal == SIGQUIT)
		;
	rl_redisplay();
	return ;
}

void	sig_handler_d(int signal)
{
	if (signal == SIGTERM)
		;
	exit(0);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler_c);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sig_handler_b);
}

void	set_signal_ign(void)
{
	signal(SIGINT, sig_handler_fork_c);
	signal(SIGQUIT, sig_handler_fork_c);
	signal(SIGTERM, sig_handler_fork_c);
}
