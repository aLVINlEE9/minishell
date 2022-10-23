/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:41:20 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:43:16 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_lstend(t_token ***cmd_lst, int count)
{
	if (cmd_lst[count + 1] == 0)
		return (1);
	return (0);
}

pid_t	exe_fork2(t_token ***cmd_lst, t_data *data, int count, int *fd)
{
	pid_t	pid;

	while (cmd_lst[count])
	{
		if (is_heredoc_here(cmd_lst[count]))
			data -> heredoc_is_still_alive = 1;
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
			exe_cmd(cmd_lst[count], data, &fd[0], is_lstend(cmd_lst, count));
		else
			parent_p(data, fd);
		count ++;
	}
	return (pid);
}

void	parent_p(t_data *data, int *fd)
{
	int	exitcode;

	if (fd[2] != -1)
		close(fd[2]);
	close(fd[1]);
	fd[2] = dup(fd[0]);
	close(fd[0]);
	if (data->heredoc_is_still_alive == 1)
	{
		wait(&exitcode);
		data->exit_code = (unsigned char)(exitcode);
		data->heredoc_is_still_alive = 0;
	}
	return ;
}

void	is_dir(char **cmd)
{
	struct stat	st;
	int			isdir;

	if (is_slash(cmd[0]))
	{
		if (stat(cmd[0], &st) != -1)
		{
			isdir = st.st_mode & 0040000;
			if (isdir)
			{
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, ": is dir\n", 9);
				exit(0);
			}
		}
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(127);
	}
	else
		print_error(cmd[0], 1);
}
