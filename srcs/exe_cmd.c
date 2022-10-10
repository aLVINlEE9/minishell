/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:23:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/10 20:04:30 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exe_fork(char ***cmd_lst, struct s_env_list *env_lst, char **envp)
{
	int		fd[3];
	int		count;
	int		status;
	pid_t	pid;

	fd[2] = -1;
	count = 0;
	while (cmd_lst[count])
	{
		printf("forked\n");
		pid = fork();
		if (pid == 0)
			exe_cmd(cmd_lst[count], envp, &fd[0]);
		else
		{
			close(fd[1]);
			fd[2] = dup(fd[0]);
			//waitpid(-1, &status, WNOHANG);
			close(fd[0]);
		}
		count ++;
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

void	exe_cmd(char **cmd_ary, char **envp, int *fd)
{
	char	**path;
	char	*temp2;
	int		count;

	count = 0;
	path = parse_env2(envp);
	if (fd[2] != -1)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	while (path[count])
	{
		temp2 = ft_strjoin(path[count], "/");
		execve(ft_strjoin(temp2, cmd_ary[0]), cmd_ary, envp);
		count ++;
	}
	printf("not exe\n");
	exit(1);
}
