/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:23:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/13 19:40:45 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_lstend(t_token ***cmd_lst, int count)
{
	if (cmd_lst[count + 1] == 0)
		return (1);
	return (0);
}

int	is_slash(char *s)
{
	char *temp;

	temp = s;
	while (*temp)
	{
		if (*temp == '/')
			return (1);
		temp ++;
	}
	return (0);
}

void	exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, char **envp, t_data *data)
{
	int		fd[4];
	int		count;
	int		status;
	int		temp;
	pid_t	pid;

	fd[2] = -1;
	fd[3] = dup(0);
	count = 0;
	while (cmd_lst[count])//pipe가 없는경우 즉 마지막 커맨드같은경우에는 stdout으로 출력되야함.
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
			exe_cmd(cmd_lst[count], envp, &fd[0], is_lstend(cmd_lst, count));
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
	if (fd[2] != -1)
		close(fd[2]);
	while (1)
	{
		temp = waitpid(-1, &status, WNOHANG);
		if (temp == -1)
			break ;
		if (temp == pid)
		{
			if ((status & 0177) ==0)
				pid = (status >> 8);
		}
	}
	close(fd[3]);
	data -> exit_code = pid;
	return ;
}

char	**parse_env2(char **env)
{
	int		i;
	char	**ret;
	char	**temp;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && \
				env[i][3] == 'H' && env[i][4] == '=')
		{
			temp = ft_split(env[i], '=');
			ret = ft_split(temp[1], ':');
			free(temp[0]);
			free(temp[1]);
			free(temp);
			return (ret);
		}
		i ++;
	}
	return (0);
}

void	exe_cmd(t_token **cmd_ary, char **envp, int *fd, int flag)
{
	char	**path;
	char	**cmd;
	char	*temp2;
	int		count;

	count = 0;
	path = parse_env2(envp);
	if (fd[2] != -1)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	cmd = make_inout_cmd(cmd_ary, fd);// 읽어내고 리다이렉션에 따라 fd를 조정한다.
	close(fd[0]);
	close(fd[3]);
	close(fd[4]);
	if (flag == 0)
		dup2(fd[1], 1);
	while (path[count])
	{
		if (!is_slash(cmd[0]))
		{
			temp2 = ft_strjoin_jh(path[count], "/");
			execve(ft_strjoin_jh(temp2, cmd[0]), cmd, envp);
			free(temp2);
		}
		else
			execve(cmd[0], cmd, envp);
		count ++;
	}
	print_error(cmd[0], 1);
}

char	**make_inout_cmd(t_token **cmd_ary, int *fd)
{
	int		count;
	int		cmd_arg_c;
	char	**ret;

	cmd_arg_c = 0;
	count = 0;
	while (cmd_ary[count])
	{
		if (cmd_ary[count] -> is_cmd == 1)
		{
			modify_inout(cmd_ary, count, fd);
			count ++;
		}
		else
			cmd_arg_c ++;
		count ++;
	}
	ret = malloc(sizeof(char *) * (cmd_arg_c + 1));
	if (!ret)
		exit(1); //error
	ret[cmd_arg_c] = 0;
	count = 0;
	cmd_arg_c = 0;
	while (cmd_ary[count])
	{
		if (cmd_ary[count] -> is_cmd == 1)
			count ++;
		else
			ret[cmd_arg_c ++] = cmd_ary[count] -> token;
		count ++;
	}
	return (ret);
}

void	modify_inout(t_token **cmd_ary, int count, int *fd)
{
	char	*s;

	if (cmd_ary[count + 1] == 0)
		print_error(0, 2);
	//if (cmd_ary[count + 1] -> is_cmd == 1)
		//exit(1);//printerror & exit;
	s = cmd_ary[count] -> token;
	if (ft_strlen(s) == 1)
	{
		if (ft_strncmp(s, "<", 1) == 0)
			cmd_leftarrow(cmd_ary[count + 1] -> token, fd);
		if (ft_strncmp(s, ">", 1) == 0)
			cmd_rightarrow(cmd_ary[count + 1] -> token, fd);
	}
	if (ft_strlen(s) == 2)
	{
		if (ft_strncmp(s, "<<", 2) == 0)
			cmd_doub_leftarrow(cmd_ary[count + 1] -> token, fd);
		if (ft_strncmp(s, ">>", 2) == 0 )
			cmd_doub_rightarrow(cmd_ary[count + 1] -> token, fd);
	}
	return ;
}
