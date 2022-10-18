/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:43:43 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/17 23:36:44 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_builtin(t_token **cmd, struct s_data_env data_env)
{
	char	**cmd2;
	int		fd[4];

	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[3] = dup(0);
	cmd2 = make_inout_cmd(cmd, &fd[0], data_env);
	if (ft_strncmp(cmd2[0], "exit", -1) == 0)
		built_exit(cmd2);
	else if (ft_strncmp(cmd2[0], "echo", -1) == 0)
		built_echo(cmd2);
	else if (ft_strncmp(cmd2[0], "cd", -1) == 0)
		built_cd(cmd2, data_env);
	/*
	else if (ft_strncmp(cmd[0], "env", -1) == 0)
		built_env();
	*/
	else if (ft_strncmp(cmd2[0], "pwd", -1) == 0)
		built_pwd();
	//else if (ft_strncmp(cmd[0], "export", -1) == 0)
	//	built_export();
	//else if (ft_strncmp(cmd[0], "unset", -1) == 0)
	//	built_unset();
	else
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
		return (0);
	}
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	return (1);
}
void	built_exit(char **cmd2)
{
	long long	code;

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

void	built_pwd(void)
{
	char	*ret;
	
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

void	built_echo(char **cmd2)
{
	int	len;

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