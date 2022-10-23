/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:01:37 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:24:19 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error2(char *s, int n)
{
	if (n == 2)
	{
		write(2, "syntax error\n", 12);
		exit(258);
	}
	if (n == 3)
	{
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory", 27);
		write(2, "\n", 1);
		exit(127);
	}
	return ;
}

void	print_error(char *s, int n)
{
	if (n == 0)
	{
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(1);
	}
	if (n == 1)
	{
		write(2, s, ft_strlen(s));
		write(2, ": command not found", 19);
		write(2, "\n", 1);
		exit(127);
	}
	if (n == 2 || n == 3)
		print_error2(s, n);
	return ;
}

void	print_built_error(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
	write(2, "\n", 1);
}
