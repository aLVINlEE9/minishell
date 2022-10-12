/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:44:14 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 20:16:14 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler_c(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		printf("minishell$ ");
	}
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler_c);// c
}
