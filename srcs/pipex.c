/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:10 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/13 21:54:31 by junhjeon         ###   ########.fr       */
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

void	free_cmdlst(t_token ***lst)
{
	int	count;

	count = 0;
	while (lst[count])
	{
		free(lst[count]);
		count ++;
	}
	free(lst);
}
static t_token	***make_cmd_list_pipe(t_token_list *token_list)
{
	t_token	*now;
	int		cmd_count;
	int		token_count;
	t_token	***cmd_list;
	t_token	**temp_list;
	
	t_cmd_make	*node;
	t_cmd_make	*start;
	t_cmd_make	*temp;

	start = 0;

	cmd_count = 0;// something wronnnnnnnnnnnng?
	token_count = 0;
	now = token_list -> head -> next;
	while (now)
	{
		if ((now -> is_cmd == 1 && *(now -> token) == '|') || now == token_list -> tail)//strcmp 로 바꿔야함
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

	token_count = 0;
	cmd_count = 0;
	temp = start;

	temp_list = malloc(sizeof(struct s_token* ) * ((temp -> count) + 1));
	if (!temp_list)
		return (0);
	temp_list[temp -> count] = 0;
	cmd_list[cmd_count] = temp_list;

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
	free_cmdmake(&start);
	//free_templist(temp_list);
	return (cmd_list);
}

static void	ft_lstadd_back(t_cmd_make **lst, t_cmd_make *new)
{
	t_cmd_make	*iter;

	iter = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		new -> next = NULL;
	}
	else
	{
		while (iter -> next != NULL)
			iter = iter -> next;
		iter -> next = new;
		new -> next = NULL;
	}
	return ;
}


static t_cmd_make	*ft_lstnew(int	c)
{
	t_cmd_make	*p;

	p = malloc(sizeof(t_cmd_make) * 1);
	if (!p)
		return (0);
		p -> count = c;
	p -> next = NULL;
	return (p);
}

void free_cmdmake(t_cmd_make **lst)
{
	t_cmd_make	*temp;
	t_cmd_make	*save;

	temp = (*lst);
	if (!(*lst))
		return ;
	save = temp -> next;
	free(temp);
	while (save)
	{
		temp = save;
		save = save -> next;
		free(temp);
	}
	return ;
}
