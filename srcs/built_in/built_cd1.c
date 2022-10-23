/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:11:16 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:33:59 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(t_env *env, char *change_val)
{
	if (!env)
		return ;
	if (!env->val)
		env->is_val_quot = 0;
	free(env->val);
	env->val = ft_strdup(change_val);
}

int	ft_is_digit(char *cmd)
{
	while (*cmd)
	{
		if (*cmd < '0' || *cmd > '9')
			return (0);
		cmd ++;
	}
	return (1);
}

int	cd_check_dash(t_data *data, t_env *env_oldpwd, \
					t_env *env_pwd)
{
	int	result;

	if (!env_oldpwd || !env_oldpwd->val)
	{
		print_built_error("cd: ", "OLDPWD not set", "");
		data->exit_code = 1;
		return (1);
	}
	result = chdir(data->oldpwd);
	write(1, data->oldpwd, ft_strlen(data->oldpwd));
	write(1, "\n", 1);
	change_env(env_oldpwd, data->pwd);
	change_env(env_pwd, data->oldpwd);
	return (0);
}

int	check_cd_error(t_data *data, char **cmd, int result)
{
	if (result == -1)
	{
		print_built_error("cd: ", cmd[1], ": No such file or directory");
		data->exit_code = 1;
		return (1);
	}
	return (0);
}

void	built_cd(char **cmd, t_data *data)
{
	t_env	*env_oldpwd;
	t_env	*env_pwd;

	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	env_oldpwd = search_env(data->env_list, "OLDPWD");
	env_pwd = search_env(data->env_list, "PWD");
	if (cmd[1] == 0 || cmd[1][0] == '~')
	{
		if (cd_check_tils(data, cmd, env_oldpwd, env_pwd))
			return ;
	}
	else if (ft_strncmp(cmd[1], "-", -1) == 0)
	{
		if (cd_check_dash(data, env_oldpwd, env_pwd))
			return ;
	}
	else
	{
		if (cd_check_else(data, cmd, env_oldpwd, env_pwd))
			return ;
	}
	data->oldpwd = data->pwd;
	data->exit_code = 0;
}
