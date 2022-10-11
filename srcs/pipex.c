/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:49:10 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/11 18:37:53 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_lstadd_back(t_cmd_make **lst, t_cmd_make *new);
static t_cmd_make	*ft_lstnew(int	c);
static t_token		***make_cmd_list_pipe(t_token_list *t);

void	pipex(t_data *data, char **envp)
{
	struct s_token_list		*token_lst;
	struct s_env_list		*env_lst;
	t_token			***cmd_lst;

	token_lst = data -> token_list;
	env_lst = data -> env_list;

	cmd_lst = make_cmd_list_pipe(token_lst);
	exe_fork(cmd_lst, env_lst, envp);
	//printing ㅇㅖ제
	/*int a = 0;
	int b = 0;
	printf("print cmd_lst\n");
	while (cmd_lst[a])
	{
		b = 0;
		while (cmd_lst[a][b])
		{
			printf("%s \n", cmd_lst[a][b] -> token);
			b++;
		}
		printf("\n");
		a ++;
	}*/
	//
}

static t_token	***make_cmd_list_pipe(t_token_list *token_list)
{
	t_token	*now;
	// t_token	*save;
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
