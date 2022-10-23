/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:07:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 15:08:50 by seungsle         ###   ########.fr       */
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
