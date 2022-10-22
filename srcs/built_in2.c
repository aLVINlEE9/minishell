/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:38:40 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/22 20:03:36 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*env_t;
	t_env	*env_oldpwd;
	t_env	*env_pwd;
	char	*temp;
	int		result;
	char	*home;
	char	*home_slash;
	char	*pwd;
	char	*oldpwd;
	char	*prev;

	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	home = data->home;
	pwd = data->pwd;
	oldpwd = data->oldpwd;
	env_oldpwd = search_env(data->env_list, "OLDPWD");
	env_pwd = search_env(data->env_list, "PWD");
	if (cmd[1] == 0 || cmd[1][0] == '~')
	{
		if (cmd[1] == 0 || ft_strncmp(cmd[1], "~", -1) == 0)
		{
			result = chdir(home);
			printf("%s\n", home);
			if (result == -1)
			{
				print_built_error("cd: ", cmd[1], ": No such file or directory");
				data->exit_code = 1;
				return ;
			}
			change_env(data->env_list, env_oldpwd, pwd);
			change_env(data->env_list, env_pwd, home);
		}
		else if (cmd[1][0] == '~' && cmd[1][1] == '/')
		{
			home_slash = ft_strjoin_jh(home, &cmd[1][1]);
			result = chdir(home_slash);
			if (result == -1)
			{
				print_built_error("cd: ", cmd[1], ": No such file or directory");
				data->exit_code = 1;
				free(home_slash);
				return ;
			}
			change_env(data->env_list, env_oldpwd, pwd);
			change_env(data->env_list, env_pwd, home_slash);
			free(home_slash);
		}
	}
	else if (ft_strncmp(cmd[1], "-", -1) == 0)
	{
		if (!env_oldpwd || !env_oldpwd->val)
		{
			print_built_error("cd: ", "OLDPWD not set", "");
			data->exit_code = 1;
			return ;
		}
		// printf("changing to %s\n", oldpwd);
		result = chdir(oldpwd);
		write(1, oldpwd, ft_strlen(oldpwd));
		write(1, "\n", 1);
		change_env(data->env_list, env_oldpwd, pwd);
		change_env(data->env_list, env_pwd, oldpwd);
		// env_t = search_env(data->env_list, "PWD");
		// if (!env_t)
		// {
		// 	return ;
		// }
		// temp = env->val;
		// env->val = env_t->val;
		// env_t->val = temp;
	}
	else
	{
		result = chdir(cmd[1]);
		if (result == -1)
		{
			print_built_error("cd: ", cmd[1], ": No such file or directory");
			// printf("cd: %s: No such file or directory\n", cmd[1]);
			data->exit_code = 1;
			return ;
		}
		change_env(data->env_list, env_oldpwd, pwd);
		pwd = getcwd(0, 1024);
		change_env(data->env_list, env_pwd, pwd);
		free(pwd);
		// change_env(data->env_list, search_env(data->env_list, "OLDPWD"), cwd);
		// change_env(data->data->env_list, data->envp, "OLDPWD", cwd);
		// free(cwd);
		// cwd = getcwd(0, 1024);
		// change_env(data->env_list, search_env(data->env_list, "PWD"), cwd);
		// change_env(data->data->env_list, data->envp, "PWD", cwd);
	}
	if (result == -1)
	{
		print_built_error("cd: ", cmd[1], ": No such file or directory");
		data->exit_code = 1;
		return ;
	}
	data->oldpwd = data->pwd;
	data->exit_code = 0;
}

void	change_env(t_env_list *env_list, t_env *env, char *change_val)
{
	if (!env)
		return ;
	if (!env->val)
		env->is_val_quot = 0;
	free(env->val);
	env->val = ft_strdup(change_val);
}
