/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:15:16 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/07 21:27:58 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

int	tokenize(t_list **token_list, char *str)
{
	char	*temp;
	int		chk;
	int		flag;

	flag = 0;
	temp = str;
	while (*temp)
	{
		if (*temp == ' ')//space
		{
			flag = 0;
		}
		else if (*temp == '"')
		{
			chk = parse_double_q(temp, token_list, flag);
			if (chk == -1)
				return (-1);
			temp += (chk + 1);
			flag = 1;
		}
		else if (*temp == 39)
		{
			chk = parse_single_q(temp, token_list, flag);
			if (chk == -1)
				return (-1);
			temp += (chk + 1);
			flag = 1;
		}
		else if (*temp == '|')
		{
			temp += parse_pipe(temp, token_list) - 1;
			flag = 0;
		}
		
		else if (*temp == '<')
		{
			temp += parse_left_arrow(temp, token_list, flag) - 1;
			flag = 0;
		}
		else if (*temp == '>')
		{
			temp += parse_right_arrow(temp, token_list, flag) - 1;
			flag = 0;;
		}
		else
		{
			chk = parse_another(temp, token_list, flag);
			temp += (chk - 1);
			flag = 1;
		}
		temp ++;
	}
	return (1);
}
