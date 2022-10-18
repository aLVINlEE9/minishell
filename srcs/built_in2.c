/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:38:40 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/18 21:59:16 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_digit(char *cmd)
{
	while (*cmd)
	{
		if (*cmd < '0' || *cmd > '9')
			return (0);
		cmd ++;
	}
	return (1);
}

void	built_cd(char **cmd2, t_token **cmd, int *fd, struct s_data_env data)
{
	int		result;
	char	*home;
	char	*cwd;
	char	*prev;
	char	**redi;

	redi = make_inout_cmd(cmd, &fd[0], data, 1);
	free(redi);
	if (!redi)
		return ;
	home = getenv("HOME");
	cwd = getcwd(0, 1024);
	if (cmd2[1] == 0 || ft_strncmp(cmd2[1], "~", -1) == 0)
	{
		result = chdir(home);
		change_env((data.envp), "OLDPWD", cwd);
		change_env((data.envp), "PWD", home);
	}
	else
	{
		result = chdir(cmd2[1]);
		change_env(data.envp, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(0, 1024);
		change_env(data.envp, "PWD", cwd);
	}
	if (result == -1)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	free(cwd);
}

void	change_env(char **env, char *key, char *change_val)
{
	int		i;
	char	*search;

	i = 0;
	search = ft_strjoin_jh(key, "=");
	while ((env)[i])
	{
		if (strncmp(env[i], search, ft_strlen(search)) == 0)
		{
			(env)[i] = ft_strjoin_jh(search, change_val);
			printf("changed  : %s \n", (env)[i]);
			free(search);
			return ;
		}
		i ++;
	}
	printf("can't find key\n");
	free(search);
	return ;
}
