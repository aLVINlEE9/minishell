/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:38:40 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/20 19:09:43 by seungsle         ###   ########.fr       */
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

void	built_cd(char **cmd, t_data *data)
{
	t_env	*env;
	t_env	*env_t;
	char	*temp;
	int		result;
	char	*home;
	char	*cwd;
	char	*prev;

	env = search_env(data->env_list, "HOME");
	home = env->val;
	// home = getenv("HOME"); // search env
	cwd = getcwd(0, 1024);
	if (cmd[1] == 0 || ft_strncmp(cmd[1], "~", -1) == 0)
	{
		result = chdir(home);
		change_env(data->env_list, search_env(data->env_list, "OLDPWD"), cwd);
		change_env(data->env_list, search_env(data->env_list, "PWD"), home);
		// change_env(data->data->env_list, (data->envp), "OLDPWD", cwd);
		// change_env(data->data->env_list, (data->envp), "PWD", home);
	}
	else if (ft_strncmp(cmd[1], "-", -1) == 0)
	{
		env = search_env(data->env_list, "OLDPWD");
		if (!env->val)
		{
			printf("cd: OLDPWD not set\n");
			free(cwd);
			return ;
		}
		result = chdir(env->val);
		env_t = search_env(data->env_list, "PWD");
		temp = env->val;
		env->val = env_t->val;
		env_t->val = temp;
	}
	else
	{
		result = chdir(cmd[1]);
		if (result == -1)
		{
			printf("cd: %s: No such file or directory\n", cmd[1]);
			free(cwd);
			return ;
		}
		change_env(data->env_list, search_env(data->env_list, "OLDPWD"), cwd);
		// change_env(data->data->env_list, data->envp, "OLDPWD", cwd);
		free(cwd);
		cwd = getcwd(0, 1024);
		change_env(data->env_list, search_env(data->env_list, "PWD"), cwd);
		// change_env(data->data->env_list, data->envp, "PWD", cwd);
	}
	if (result == -1)
		printf("cd: %s: No such file or directory\n", cmd[1]);
	free(cwd);
}

void	change_env(t_env_list *env_list, t_env *env, char *change_val)
{
	// printf("%d %s\n", !env->val, change_val);
	if (!env->val)
		env->is_val_quot = 0;
	free(env->val);
	// printf("%s\n", temp);
	env->val = ft_strdup(change_val);
	// printf("%s\n", env->val);
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
