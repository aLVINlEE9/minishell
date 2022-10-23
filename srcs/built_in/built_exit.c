/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:09:39 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:29:46 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_exit(char **cmd2, int flag, t_data *data)
{
	long long	code;

	code = 0;
	if (cmd2[1] == 0)
	{
		if (flag == 1)
			write(2, "exit\n", 5);
		termi_old(data->termi);
		exit(0);
	}
	else
		built_exit_args(cmd2, flag, data, code);
}

void	built_exit_args(char **cmd2, int flag, t_data *data, long long code)
{
	if (ft_is_digit(cmd2[1]))
	{
		if (cmd2[2] != 0)
		{
			if (flag == 1)
			{
				write(2, "exit\n", 5);
				write(2, "too many args\n", 14);
				data->exit_code = 1;
			}
			return ;
		}
		code = ft_atol(cmd2[1]);
		termi_old(data->termi);
		exit((unsigned char)code);
	}
	write(2, "numeric arg required\n", 21);
	termi_old(data->termi);
	exit(255);
}
