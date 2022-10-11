/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:23:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/11 21:36:13 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_lstend(t_token ***cmd_lst, int count)
{
	if (cmd_lst[count + 1] == 0)
		return (1);
	return (0);
}

void	exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, char **envp)
{
	int		fd[3];
	int		count;
	int		status;
	pid_t	pid;

	fd[2] = -1;
	count = 0;
	while (cmd_lst[count])//pipe가 없는경우 즉 마지막 커맨드같은경우에는 stdout으로 출력되야함.
	{
		printf("forked\n");
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
			printf("fd[2] : %d\n", fd[2]);
			//waitpid(-1, &status, WNOHANG);
			close(fd[0]);
		}
		count ++;
	}
	if (fd[2] != -1)
		close(fd[2]);
	while (1)
	{
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == -1)
			break ;
	}
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

	printf("child fd[2] = %d \n", fd[2]);
	//printf("exe_cmd\n");
	count = 0;
	path = parse_env2(envp);
	if (flag == 0)
		dup2(fd[1], 1);
	cmd = make_inout_cmd(cmd_ary, fd);// 읽어내고 리다이렉션에 따라 fd를 조정한다.
	if (fd[2] != -1)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	//printf("cmd_count\n");
	/*
	while (cmd[count])
	{
		printf("cmd : %s\n", cmd[count]);
		count ++;
	}
	*/
	close(fd[0]);
	while (path[count])
	{
		temp2 = ft_strjoin_jh(path[count], "/");
		execve(ft_strjoin_jh(temp2, cmd[0]), cmd, envp);
		count ++;
		free(temp2);
	}
	exit(1);
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
		return(0); //error
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
		exit(1);//printerror & exit;
	if (cmd_ary[count + 1] -> is_cmd == 1)
		exit(1);//printerror & exit;
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
		{
			printf(">> is working\n");
			cmd_doub_rightarrow(cmd_ary[count + 1] -> token, fd);
		}
	}
	return ;
}
