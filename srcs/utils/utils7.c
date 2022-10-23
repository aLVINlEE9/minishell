/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:00:18 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 16:21:02 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_oldpath(void)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 3);
	ret[0] = ft_strdup("export");
	ret[1] = ft_strdup("OLDPWD");
	ret[2] = 0;
	return (ret);
}

void	free_cmd(char **cmd)
{
	free(cmd[0]);
	free(cmd[1]);
	free(cmd);
}

void	update_home(t_data *data)
{
	t_env	*env;

	env = search_env(data->env_list, "HOME");
	if (env)
		data->home = ft_strdup(env->val);
	data->oldpwd = NULL;
	data->pwd = getcwd(NULL, 0);
}

int	check_echo_opt(char **cmd2, int len)
{
	int	count;
	int	opt_count;

	count = 0;
	opt_count = 0;
	if (cmd2[1] == 0)
		return (0);
	while (cmd2[len])
	{
		count = 0;
		if (cmd2[len][count ++] == '-')
		{
			while (cmd2[len][count])
			{
				if (cmd2[len][count ++] != 'n')
					return (opt_count);
			}
			opt_count ++;
			len ++;
		}
		else
			break ;
	}
	return (opt_count);
}

void	built_exit_args(char **cmd2, int flag, t_data *data, long long code)
{
	if (ft_is_digit(cmd2[1]))
	{
		if (cmd2[2] != 0)
		{
			if (flag == 1)
			{
				write(2, "exit\n", 5);
				write(2, "too many args\n", 14);
				data->exit_code = 1;
			}
			return ;
		}
		code = ft_atol(cmd2[1]);
		termi_old(data->termi);
		exit((unsigned char)code);
	}
	write(2, "numeric arg required\n", 21);
	termi_old(data->termi);
	exit(255);
}
