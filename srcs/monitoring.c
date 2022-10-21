/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:37:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 18:06:34 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	monitoring(t_data *data, int pid, int *fd)
{
	int	temp;
	int	status;

	if (fd[2] != -1)
		close(fd[2]);
	signal(SIGINT, sig_handler_fork_c);
	signal(SIGQUIT, sig_handler_fork_b);
	while (1)
	{
		temp = waitpid(-1, &status, WNOHANG);
		if (temp == -1)
			break ;
		if (temp == pid)
		{
			if ((status & 0177) == 0)
				pid = (status >> 8);
			if (WIFSIGNALED(status))
				pid = WTERMSIG(status) + 128;
		}
	}
	close(fd[3]);
	data -> exit_code = pid;
	return ;
}
