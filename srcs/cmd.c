/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:30:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/12 14:05:18 by seungsle         ###   ########.fr       */
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
	//heredoc;
    (void)s;
    (void)fd;
	return ;
}

void	cmd_doub_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 2);
	return ;
}
