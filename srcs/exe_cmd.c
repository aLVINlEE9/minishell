/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:23:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:18:24 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, \
		t_data *data)
{
	int		fd[5];
	int		count;
	pid_t	pid;
	int		exitcode;

	fd[2] = -1;
	fd[3] = dup(0);
	fd[4] = dup(1);
	count = 0;
	termi_old(data->termi, 0);
	pid = exe_fork2(cmd_lst, data, 0, &fd[0]);
	monitoring(data, pid, &fd[0]);
}

void	exe_cmd(t_token **cmd_ary, t_data *data, int *fd, int flag)
{
	char		**cmd;

	if (fd[2] != -1)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	if (flag == 0)
		dup2(fd[1], 1);
	if (check_builtin(cmd_ary, data))
		exit(0);
	else
		cmd = make_inout_cmd(cmd_ary, fd, data);
	close(fd[0]);
	exe_cmd2(cmd, data);
	is_dir(cmd);
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
