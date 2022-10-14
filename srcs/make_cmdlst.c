/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:54:31 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 21:12:00 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_cmd(t_token **cmd_ary, int cmd_arg_c)//cmd_exe로 옮겨야하나?
{
	int		count;
	char	**ret;

	ret = malloc(sizeof(char *) * (cmd_arg_c + 1));
	if (!ret)
		exit(1); // error
	ret[cmd_arg_c] = 0;
	count = 0;
	cmd_arg_c = 0;
	while (cmd_ary[count])
	{
		if (cmd_ary[count] -> is_cmd == 1)
			count ++;
		else
			ret[cmd_arg_c ++] = cmd_ary[count] -> token;
		count ++;
	}
	return (ret);
}
