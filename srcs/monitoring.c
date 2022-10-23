/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:37:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:22:13 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	monitoring(t_data *data, int pid, int *fd)
{
	int	ret;

	if (fd[2] != -1)
		close(fd[2]);
	set_signal_ign();
	ret = monitoring_pid(pid, 0);
	close(fd[3]);
	close(fd[4]);
	data -> exit_code = (unsigned char)ret;
	return ;
}

int	monitoring_pid(pid_t last_pid, int ret)
{
	int		status;
	int		pid;
	pid_t	temp;

	while (1)
	{
		temp = waitpid(-1, &status, WNOHANG);
		if (temp == -1)
			break ;
		if (temp == last_pid)
		{
			if ((status & 0177) == 0)
				ret = (status >> 8);
			if (WIFSIGNALED(status))
			{
				ret = WTERMSIG(status) + 128;
				if (ret == 131)
					write(2, "Quit: 3", 7);
				write(2, "\n", 1);
			}
		}
	}
	return (ret);
}
