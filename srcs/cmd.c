/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:30:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 22:22:43 by junhjeon         ###   ########.fr       */
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

	//dup2(fd[4], 0);
	while (1)
	{
		str = readline("> ");
		if (str == 0)
		{
			write(2, "\033[1A", 4);
			write(2, "\033[2C", 4);
			break ;
		}
		if (ft_strncmp(str, s, ft_strlen(s)) == 0) // 비교함수 고쳐야 함.
			break ;
		write(fd[4], str, ft_strlen(str));
		write(fd[4], "\n", 1);
		free(str);
	}
	dup2(fd[3], 0);
	return ;
}

void	cmd_doub_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 2);
	return ;
}
