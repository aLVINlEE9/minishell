/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:44:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 17:55:18 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_slash(char *s)
{
	char	*temp;

	temp = s;
	while (*temp)
	{
		if (*temp == '/')
			return (1);
		temp ++;
	}
	return (0);
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

int	chk_builtin_infork(char **cmd2, t_data *data)
{
	if (ft_strncmp(cmd2[0], "exit", -1) == 0)
		built_exit(cmd2, 0, data);
	else if (ft_strncmp(cmd2[0], "echo", -1) == 0)
		built_echo(cmd2);
	else if (ft_strncmp(cmd2[0], "cd", -1) == 0)
		built_cd(cmd2, data);
	else if (ft_strncmp(cmd2[0], "env", -1) == 0)
		built_env(data);
	else if (ft_strncmp(cmd2[0], "pwd", -1) == 0)
		built_pwd(data);
	else if (ft_strncmp(cmd2[0], "export", -1) == 0)
	 	built_export(data, cmd2);
	else if (ft_strncmp(cmd2[0], "unset", -1) == 0)
		built_unset(data, cmd2);
	else
		return (0);
	return (1);
}

void	exe_cmd2(char **cmd, t_data *data)
{
	char	**path;
	char	*temp2;
    char    **temp;
	int		count;

	count = 0;
	temp = update_env(data, 0);
	path = parse_env2(temp);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (path[count])
	{
		if (!is_slash(cmd[0]))
		{
			temp2 = ft_strjoin_jh(path[count], "/");
			execve(ft_strjoin_jh(temp2, cmd[0]), cmd, temp);
			free(temp2);
		}
		else
			execve(cmd[0], cmd, temp);
		count ++;
	}
	free_env(temp);
}
