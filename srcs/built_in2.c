/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:38:40 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/17 21:27:56 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_digit(char *cmd)
{
	while (*cmd)
	{
		if (*cmd < '0' || *cmd > '9')
			return (0);
		cmd ++;
	}
	return (1);
}
void	built_cd(void)
{

}
