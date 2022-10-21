/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:01:37 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:17 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (n == 2)
	{
		write(2, "syntax error\n", 12);
		exit(258);
	}
}
