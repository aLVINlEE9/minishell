/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:36:48 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 16:16:23 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_iofile(char *s, int *fd, int count)
{
	char	*filename;
	int		fd_iofile;

	if (s[0] != '/')
		filename = ft_strjoin_jh("./", s);
	else
		filename = ft_strjoin_jh("", s);
	if (count == 1)
	{
		fd_iofile = open(filename, O_RDONLY);
		if (fd_iofile == -1 || access(filename, R_OK) == -1)
			exit(1); // printerror
		else
		{
			dup2(fd_iofile, 0);
			close(fd_iofile);
		}
		free(filename);
		return ;
	}
	if (count == 2)
	{
		fd_iofile = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_iofile == -1 || access(filename, W_OK) == -1)
			exit(1);// printerror
		dup2(fd_iofile, 1);
		free(filename);
		return ;
	}
	if (count == 0)
	{
		fd_iofile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_iofile == -1 || access(filename, W_OK) == -1)
			exit(1); // printerror need
		dup2(fd_iofile, 1); // 나중엔 풀어줘야함 
		free(filename);
	}
}
