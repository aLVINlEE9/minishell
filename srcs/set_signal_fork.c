/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:40:45 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 19:37:53 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
