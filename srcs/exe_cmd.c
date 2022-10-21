/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:23:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:17 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_lstend(t_token ***cmd_lst, int count)
{
	if (cmd_lst[count + 1] == 0)
		return (1);
	return (0);
}

void	exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, \
		t_data *data)
{
	int		fd[4];
	int		count;
	pid_t	pid;

	fd[2] = -1;
	fd[3] = dup(0);
	count = 0;
	while (cmd_lst[count])
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
			exe_cmd(cmd_lst[count], data, &fd[0], is_lstend(cmd_lst, count));
		else
		{
			if (fd[2] != -1)
				close(fd[2]);
			close(fd[1]);
			fd[2] = dup(fd[0]);
			close(fd[0]);
		}
		count ++;
	}
	monitoring(data, pid, &fd[0]);
}

void	exe_cmd(t_token **cmd_ary, t_data *data, int *fd, int flag)
{
	char		**cmd;
	struct stat	st;
	if (fd[2] != -1)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	cmd = make_inout_cmd(cmd_ary, fd, data);// 읽어내고 리다이렉션에 따라 fd를 조정한다.
	close(fd[0]);
	close(fd[3]);
	close(fd[4]);
	if (flag == 0)
		dup2(fd[1], 1);
	if (chk_builtin_infork(cmd, data))//built in command check.
		exit(0);
	else
		exe_cmd2(cmd, data);
	if (is_slash(cmd[0]))
	{
		if (stat(cmd[0], &st) != -1)
			if (/*S_ISDIR(st.st_mode)*/ 0040000 & st.st_mode)
			{
				write(2, cmd[0], ft_strlen(cmd[0]));
				write(2, ": is dir\n", 9);
				exit(0);
			}
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(0);
	}
	else
		print_error(cmd[0], 1);
}

char	**make_inout_cmd(t_token **cmd_ary, int *fd, t_data *data)
{
	int		count;
	int		cmd_arg_c;
	char	**ret;

	cmd_arg_c = 0;
	count = 0;
	while (cmd_ary[count])
	{
		if (cmd_ary[count]->is_cmd == 1)
		{
			modify_inout(cmd_ary, count, fd, data);
			count ++;
		}
		else
			cmd_arg_c ++;
		count ++;
	}
	ret = make_cmd(cmd_ary, cmd_arg_c);
	return (ret);
}

void	modify_inout(t_token **cmd_ary, int count, int *fd, t_data *data)
{
	char	*s;

	if (cmd_ary[count + 1] == 0)
		print_error(0, 2);
	//if (cmd_ary[count + 1] -> is_cmd == 1)  syntax error?
		//exit(1);//printerror & exit;
	s = cmd_ary[count]->token;
	if (ft_strlen(s) == 1)
	{
		if (ft_strncmp(s, "<", -1) == 0)
			cmd_leftarrow(cmd_ary[count + 1]->token, fd);
		if (ft_strncmp(s, ">", -1) == 0)
			cmd_rightarrow(cmd_ary[count + 1]->token, fd);
	}
	if (ft_strlen(s) == 2)
	{
		if (ft_strncmp(s, "<<", -1) == 0)
			cmd_doub_leftarrow(cmd_ary[count + 1]->token, fd, data);
		if (ft_strncmp(s, ">>", -1) == 0)
			cmd_doub_rightarrow(cmd_ary[count + 1]->token, fd);
	}
	return ;
}
