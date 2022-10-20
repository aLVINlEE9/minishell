/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:38:40 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/20 16:41:04 by seungsle         ###   ########.fr       */
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

void	built_cd(char **cmd, struct s_data_env *data)
{
	t_env	*env;
	int		result;
	char	*home;
	char	*cwd;
	char	*prev;

	env = search_env(data->data->env_list, "HOME");
	home = env->val;
	// home = getenv("HOME"); // search env
	cwd = getcwd(0, 1024);
	if (cmd[1] == 0 || ft_strncmp(cmd[1], "~", -1) == 0)
	{
		result = chdir(home);
		change_env(search_env(data->data->env_list, "OLDPWD"), cwd);
		change_env(search_env(data->data->env_list, "PWD"), home);
		// change_env((data->envp), "OLDPWD", cwd);
		// change_env((data->envp), "PWD", home);
	}
	else
	{
		result = chdir(cmd[1]);
		change_env(search_env(data->data->env_list, "OLDPWD"), cwd);
		// change_env(data->envp, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(0, 1024);
		change_env(search_env(data->data->env_list, "PWD"), cwd);
		// change_env(data->envp, "PWD", cwd);
	}
	if (result == -1)
		printf("cd: %s: No such file or directory\n", cmd[1]);
	free(cwd);
}

void	change_env(t_env *env, char *change_val)
{
	free(env->val);
	env->val = ft_strdup(change_val);
	// int		i;
	// char	*search;

	// i = 0;
	// search = ft_strjoin_jh(key, "=");
	// while ((env)[i])
	// {
	// 	if (strncmp(env[i], search, ft_strlen(search)) == 0)
	// 	{
	// 		(env)[i] = ft_strjoin_jh(search, change_val);
	// 		printf("changed  : %s \n", (env)[i]);
	// 		free(search);
	// 		return ;
	// 	}
	// 	i ++;
	// }
	// printf("can't find key\n");
	// free(search);
	// return ;
}
