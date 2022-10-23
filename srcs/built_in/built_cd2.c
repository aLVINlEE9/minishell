/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:42:11 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:04:01 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_check_tils(t_data *data, char **cmd, t_env *env_oldpwd, t_env *env_pwd)
{
	if (cmd[1] == 0 || ft_strncmp(cmd[1], "~", -1) == 0)
	{
		if (cd_check_til(data, cmd, env_oldpwd, env_pwd))
			return (1);
	}
	else if (cmd[1][0] == '~' && cmd[1][1] == '/')
	{
		if (cd_check_after_til(data, cmd, env_oldpwd, env_pwd))
			return (1);
	}
	return (0);
}

int	cd_check_til(t_data *data, char **cmd, t_env *env_oldpwd, t_env *env_pwd)
{
	int	result;

	result = chdir(data->home);
	if (check_cd_error(data, cmd, result))
		return (1);
	change_env(data->env_list, env_oldpwd, data->pwd);
	change_env(data->env_list, env_pwd, data->home);
	return (0);
}

int	cd_check_after_til(t_data *data, char **cmd, t_env *env_oldpwd, \
					t_env *env_pwd)
{
	char	*home_slash;
	int		result;

	home_slash = ft_strjoin_jh(data->home, &cmd[1][1]);
	result = chdir(home_slash);
	if (check_cd_error(data, cmd, result))
	{
		free(home_slash);
		return (1);
	}
	change_env(data->env_list, env_oldpwd, data->pwd);
	change_env(data->env_list, env_pwd, home_slash);
	free(home_slash);
	return (0);
}

int	cd_check_else(t_data *data, char **cmd, t_env *env_oldpwd, \
					t_env *env_pwd)
{
	int	result;

	result = chdir(cmd[1]);
	if (check_cd_error(data, cmd, result))
		return (1);
	cd_check_else_sub(data, data->pwd, env_oldpwd, env_pwd);
	return (0);
}

void	cd_check_else_sub(t_data *data, char *pwd, t_env *env_oldpwd, \
					t_env *env_pwd)
{
	char	*newpwd;

	change_env(data->env_list, env_oldpwd, pwd);
	newpwd = getcwd(0, 1024);
	change_env(data->env_list, env_pwd, newpwd);
	free(newpwd);
}
