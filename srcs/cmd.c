/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:30:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/17 18:14:40 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_leftarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 1);
}

void	cmd_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 0);
}

void	cmd_doub_leftarrow(char *s, int *fd, struct s_data_env data_env)
{
	char	*str;
	char	*ret;
	int		temp[2];
	struct	s_dollar_str	str_temp;

	pipe(temp);
	str_temp.str = str;
	str_temp.fd_temp = &temp[0];
	dup2(fd[3], 0);
	cmd_heredoc_write(str_temp, ret, s, data_env);
	dup2(temp[0], 0);
	close(temp[0]);
	close(temp[1]);
	return ;
}

void	cmd_doub_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 2);
	return ;
}

void	cmd_heredoc_write(struct s_dollar_str t_str, char *ret, char *s, struct s_data_env data_env)
{
	while (1)
	{
		t_str.str = readline("> ");
		if (t_str.str == 0)
		{
			write(2, "\033[1A", 4);
			write(2, "\033[2C", 4);
			break ;
		}
		if (ft_strncmp(t_str.str, s, -1) == 0)
		{	
			free(t_str.str);
			break ;
		}
		ret = dollarparsing(t_str.str, 0, 0, data_env);
		if (!ret)
			write(t_str.fd_temp[1], t_str.str, ft_strlen(t_str.str));
		else
		{
			write(t_str.fd_temp[1], ret, ft_strlen(ret));
			free(ret);
		}
		write(t_str.fd_temp[1], "\n", 1);
		free(t_str.str);
	}
}
