/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:44:14 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 22:16:51 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	rl_redisplay();
	return ;
}

void	sig_handler_d(int signal)
{
	exit(0);
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler_c);// c
	signal(SIGQUIT, sig_handler_b);//b
	signal(SIGTERM, sig_handler_d);
}
