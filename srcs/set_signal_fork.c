/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:40:45 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:24:48 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler_fork_c(int signal)
{
	return ;
}

void	sig_handler_fork_d(int signal)
{
	return ;
}

void	sig_handler_fork_b(int signal)
{
	return ;
}

void	set_signal_fork(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
