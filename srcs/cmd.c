/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:30:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 20:34:51 by junhjeon         ###   ########.fr       */
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

void	cmd_doub_leftarrow(char *s, int *fd)
{
	char	*str;
	char	*ret;
	int		temp[2];

	pipe(temp);
	dup2(fd[3], 0);
	cmd_heredoc_write(str, ret, &temp[0], s);
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

void	cmd_heredoc_write(char *str, char *ret, int *temp, char *s)
{
	while (1)
	{
		str = readline("> ");
		if (str == 0)
		{
			write(2, "\033[1A", 4);
			write(2, "\033[2C", 4);
			break ;
		}
		if (ft_strncmp(str, s, -1) == 0) // 비교 함수 고쳐야함.
		{	
			free(str);
			break ;
		}
		ret = dollarparsing(str, 0, 0);
		if (!ret)
			write(temp[1], str, ft_strlen(str));
		else
		{
			write(temp[1], ret, ft_strlen(ret));
			free(ret);
		}
		write(temp[1], "\n", 1);
		free(str);
	}
}
