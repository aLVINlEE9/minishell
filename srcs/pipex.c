/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:10 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/18 17:59:04 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipex(t_data *data, char **envp)
{
	struct s_token_list		*token_lst;
	struct s_env_list		*env_lst;
	t_token					***cmd_lst;
	struct s_data_env		data_env;

	token_lst = data -> token_list;
	env_lst = data -> env_list;
	cmd_lst = make_cmd_list_pipe(token_lst);
	data_env.envp = envp;
	data_env.data = data;
	if (cmd_lst[1] == 0 && check_builtin(cmd_lst[0], &data_env))//built in one line case
		;
	else
		exe_fork(cmd_lst, env_lst, &data_env);
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
	//free_templist(temp_list);
	return (cmd_list);
}
