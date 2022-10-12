/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:36:48 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 14:06:49 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_iofile(char *s, int *fd, int count)
{
	char	*filename;
	int		fd_iofile;

    (void)fd;
	if (s[0] != '/')
		filename = ft_strjoin("./", s);
	else
		filename = ft_strjoin("", s);
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
		fd_iofile = open(filename, O_WRONLY | O_CREAT | O_APPEND | O_EXCL, 0644);
			if (fd_iofile == -1 || access(filename, W_OK) == -1)
				exit(1);// printerror
		dup2(fd_iofile, 1);
	}
	fd_iofile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_iofile == -1 || access(filename, W_OK) == -1)
		exit(1); // printerror need
	dup2(fd_iofile, 1);
}
