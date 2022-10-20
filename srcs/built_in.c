/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:43:43 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/19 18:38:02 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_builtin(t_token **cmd, struct s_data_env *data_env)
{
	char	**cmd2;

	cmd2 = make_inout_cmd(cmd, &fd[0], data_env, 0);
	if (ft_strncmp(cmd2[0], "exit", -1) == 0)
		built_exit(cmd2, cmd, &fd[0], data_env);
	else if (ft_strncmp(cmd2[0], "echo", -1) == 0)
		built_echo(cmd2, cmd, &fd[0], data_env);
	else if (ft_strncmp(cmd2[0], "cd", -1) == 0)
		built_cd(cmd2, data_env);
	else if (ft_strncmp(cmd2[0], "env", -1) == 0)
		built_env(data_env);
	else if (ft_strncmp(cmd2[0], "pwd", -1) == 0)
		built_pwd();
	else if (ft_strncmp(cmd2[0], "export", -1) == 0)
	 	built_export(data_env, cmd2);
	else if (ft_strncmp(cmd2[0], "unset", -1) == 0)
		built_unset(data_env, cmd2);
	else
	{
		free(cmd2);
		return (0);
	}
	free(cmd2);
	return (1);
}
void	built_exit(char **cmd2, t_token **cmd, int *fd, struct s_data_env data_env)
{
	long long	code;
	char		**redi;

	redi = make_inout_cmd(cmd, &fd[0], data_env, 1);
	if (!redi)
		return ;
	free(redi);
	code = 0;
	if (cmd2[1] == 0)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	else
	{
		if (ft_is_digit(cmd2[1]))
		{
			if (cmd2[2] != 0)
			{
				write(2, "exit\n", 5);
				write(2, "too many args\n", 14);
				return ;
			}
			code = ft_atol(cmd2[1]);
			exit((unsigned char)code);
		}
		write(2, "numeric arg required\n", 21);
		exit(255);
	}
}

void	built_pwd(t_token **cmd, int *fd, struct s_data_env data_env)
{
	char	*ret;
	char	**redi;

	redi = make_inout_cmd(cmd, &fd[0], data_env, 1);
	free(redi);
	ret = getenv("PWD");
	write(1, ret, ft_strlen(ret));
	write(1, "\n", 1);
}

int	check_echo_opt(char **cmd2)
{
	int	len;
	int	count;
	int	opt_count;

	len = 1;
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

void	built_echo(char **cmd2, t_token **cmd, int *fd, struct s_data_env data_env)
{
	int		len;
	char	**redi;

	redi = make_inout_cmd(cmd, &fd[0], data_env, 1);
	if (!redi)
		return ;
	free(redi);
	len = check_echo_opt(cmd2);
	if (len)
	{
		while (cmd2[len + 1])
		{
			write(1, cmd2[len + 1], ft_strlen(cmd2[len + 1]));
			if (cmd2[len + 2] != 0)
				write(1, " ", 1);
			len ++;
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
}
