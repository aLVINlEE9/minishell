/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:10:29 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 15:10:37 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	built_echo(char **cmd2, t_data *data)
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
	data->exit_code = 0;
}