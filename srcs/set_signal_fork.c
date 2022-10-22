/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:40:45 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/22 19:01:53 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_fork_c(int signal)
{
	write(2, "\n", 1);
}

void	sig_handler_fork_d(int signal)
{
	exit(0);
}

void	sig_handler_fork_b(int signal)
{
	write(2, "Quit: 3\n", 8);
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, sig_handler_fork_b);

}
