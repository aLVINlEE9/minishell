/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:37:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/22 19:02:52 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	monitoring(t_data *data, int pid, int *fd)
{
	if (fd[2] != -1)
		close(fd[2]);
	pid = monitoring_pid(pid, 0);
	close(fd[3]);
	close(fd[4]);
	set_signal();
	data -> exit_code = pid;
	return ;
}

int	monitoring_pid(int last_pid, int ret)
{
	int	status;
	int	pid;
	int	temp;

	while (1)
	{
		temp = waitpid(-1, &status, WNOHANG);
		if (temp == -1)
			break ;
		if (temp == pid)
		{
			if ((status & 0177) == 0)
				ret = (status >> 8);
			if (WIFSIGNALED(status))
			{
				ret = WTERMSIG(status) + 128;
				if (ret == 131)
					write(2, "Quit: 3", 7);
				printf("\n");
			}
		}
	}
	return (ret);
}
