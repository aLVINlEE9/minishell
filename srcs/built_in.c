/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:43:43 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 16:24:12 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_sub(char **cmd2, t_data *data)
{
	if (ft_strncmp(cmd2[0], "exit", -1) == 0)
		built_exit(cmd2, 1, data);
	else if (ft_strncmp(cmd2[0], "echo", -1) == 0)
		built_echo(cmd2, data);
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

int	check_builtin(t_token **cmd, t_data *data)
{
	char	**cmd2;
	char	*first_cmd;
	int		fd[4];

	first_cmd = find_first_cmd(cmd);
	if (!is_firstcmd_builtin(first_cmd))
		return (0);
	cmd2 = make_inout_cmd(cmd, &fd[0], data);
	if (check_builtin_sub(cmd2, data))
	{
		free(cmd2);
		return (1);
	}
	else
	{
		free(cmd2);
		return (0);
	}
}

void	built_exit(char **cmd2, int flag, t_data *data)
{
	long long	code;

	code = 0;
	if (cmd2[1] == 0)
	{
		if (flag == 1)
			write(2, "exit\n", 5);
		termi_old(data->termi);
		exit(0);
	}
	else
		built_exit_args(cmd2, flag, data, code);
}

void	built_pwd(t_data *data)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	write(1, ret, ft_strlen(ret));
	write(1, "\n", 1);
	free(ret);
	data->exit_code = 0;
}

void	built_echo(char **cmd2, t_data *data)
{
	int	len;

	len = check_echo_opt(cmd2, 1);
	if (len)
	{
		while (cmd2[len + 1])
		{
			write(1, cmd2[len + 1], ft_strlen(cmd2[len + 1]));
			if (cmd2[2 + len ++] != 0)
				write(1, " ", 1);
		}
	}
	else
	{
		len = 1;
		while (cmd2[len])
		{
			write(1, cmd2[len], ft_strlen(cmd2[len]));
			if (cmd2[len + 1] != 0)
				write(1, " ", 1);
			len ++;
		}
		write(1, "\n", 1);
	}
	data->exit_code = 0;
}
