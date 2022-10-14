/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:44:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 20:59:13 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	exe_cmd2(char **cmd, char **envp)
{
	char	**path;
	char	*temp2;
	int		count;

	count = 0;
	path = parse_env2(envp);
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
}
