/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:37:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/19 17:18:11 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	monitoring(t_data *data, int pid, int *fd)
{
	int	temp;
	int	status;

	if (fd[2] != -1)
		close(fd[2]);
	while (1)
	{
		temp = waitpid(-1, &status, WNOHANG);
		if (temp == -1)
			break ;
		if (temp == pid)
		{
			if ((status & 0177) == 0)
				pid = (status >> 8);
		}
	}
	close(fd[3]);
	data -> exit_code = pid;
	return ;
}
