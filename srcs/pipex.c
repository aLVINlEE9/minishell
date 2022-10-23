/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:10 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 16:15:06 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_data *data)
{
	struct s_token_list		*token_lst;
	struct s_env_list		*env_lst;
	t_token					***cmd_lst;

	token_lst = data -> token_list;
	set_signal_fork();
	env_lst = data -> env_list;
	cmd_lst = make_cmd_list_pipe(token_lst);
	if (cmd_lst[1] == 0 && check_builtin(cmd_lst[0], data))
		;
	else
		exe_fork(cmd_lst, data);
	free_cmdlst(cmd_lst);
}

t_token	***make_cmd_list_pipe(t_token_list *token_list)
{
	t_token		***cmd_list;
	t_token		**temp_list;
	t_cmd_make	*start;
	t_cmd_make	*temp;

	start = 0;
	cmd_list = make_t_cmd_make_lst(token_list, &start, 0, 0);
	temp = start;
	temp_list = malloc(sizeof(struct s_token *) * ((temp -> count) + 1));
	if (!temp_list)
		return (0);
	temp_list[temp -> count] = 0;
	cmd_list[0] = temp_list;
	whatisit(token_list, cmd_list, start, temp_list);
	free_cmdmake(&start);
	return (cmd_list);
}
