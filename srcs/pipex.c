/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:10 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 21:39:11 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_lstadd_back(t_cmd_make **lst, t_cmd_make *new);
static t_cmd_make	*ft_lstnew(int	c);
static t_token		***make_cmd_list_pipe(t_token_list *t);
void	free_cmdmake(t_cmd_make **lst);
void	free_cmdlst(t_token ***cmd_lst);

void	pipex(t_data *data, char **envp)
{
	struct s_token_list		*token_lst;
	struct s_env_list		*env_lst;
	t_token			***cmd_lst;

	token_lst = data -> token_list;
	env_lst = data -> env_list;

	cmd_lst = make_cmd_list_pipe(token_lst);
	exe_fork(cmd_lst, env_lst, envp, data);
	free_cmdlst(cmd_lst);
}

static t_token	***make_cmd_list_pipe(t_token_list *token_list)
{
	t_token	*now;
	//int		cmd_count;
	//int		token_count;
	t_token	***cmd_list;
	t_token	**temp_list;
	
	//t_cmd_make	*node;
	t_cmd_make	*start;
	t_cmd_make	*temp;

	start = 0;

	//cmd_count = 0;
	//token_count = 0;
	make_t_cmd_make_lst(token_list, &start, 0, 0);
	/*
	now = token_list -> head -> next;
	while (now)
	{
		if ((now -> is_cmd == 1 && *(now -> token) == '|') || now == token_list -> tail)
		{
			cmd_count ++;
			node = ft_lstnew(token_count);
			ft_lstadd_back(&start, node);
			token_count = 0;
		}
		else
			token_count ++;
		now = now -> next;
	}
	
	cmd_list = malloc(sizeof(struct s_token** ) * (cmd_count + 1));
	if (!(cmd_list))
		return (0);
	cmd_list[cmd_count] = 0;
	*/
	token_count = 0;
	cmd_count = 0;
	temp = start;

	temp_list = malloc(sizeof(struct s_token* ) * ((temp -> count) + 1));
	if (!temp_list)
		return (0);
	temp_list[temp -> count] = 0;
	cmd_list[cmd_count] = temp_list;
	whatisit(token_list, cmd_list, start);
	/*
	now = token_list -> head -> next;
	while (now != token_list -> tail)
	{
		if (now -> is_cmd  == 1 && *(now -> token) == '|')
		{
			temp = temp -> next;
			temp_list = malloc(sizeof(struct s_token) * ((temp -> count) + 1));
			if (!temp_list)
				return (0);
			temp_list[temp -> count] = 0;
			cmd_count ++;
			cmd_list[cmd_count] = temp_list;
			token_count = 0;
		}
		else
		{
			temp_list[token_count] = now;
			token_count ++;
		}
		now = now -> next;
	}
	*/
	free_cmdmake(&start);
	//free_templist(temp_list);
	return (cmd_list);
}
