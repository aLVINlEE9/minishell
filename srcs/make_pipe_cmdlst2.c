/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_cmdlst2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:16:09 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:21:52 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	***make_t_cmd_make_lst(t_token_list *tok_lst, \
		t_cmd_make **start, int cmd_count, int token_count)
{
	t_token		*now;
	t_cmd_make	*node;
	t_token		***cmd_list;

	now = tok_lst -> head -> next;
	while (now)
	{
		if ((now -> is_cmd == 1 && *(now -> token) == '|') \
				|| now == tok_lst -> tail)
		{
			(cmd_count)++;
			node = ft_lstnew(token_count);
			ft_lstadd_back(start, node);
			(token_count) = 0;
		}
		else
			(token_count)++;
		now = now -> next;
	}
	cmd_list = malloc(sizeof(struct s_token **) * (cmd_count + 1));
	if (!(cmd_list))
		exit(1);
	cmd_list[cmd_count] = 0;
	return (cmd_list);
}

void	whatisit(t_token_list *tok_lst, t_token ***cmd_list, \
		t_cmd_make *start, t_token **temp_list)
{
	t_token	*now;
	int		token_count;
	int		cmd_count;

	token_count = 0;
	cmd_count = 0;
	now = tok_lst -> head -> next;
	while (now != tok_lst -> tail)
	{
		if (now -> is_cmd == 1 && *(now -> token) == '|')
		{
			start = start -> next;
			temp_list = malloc(sizeof(struct s_token) * ((start -> count) + 1));
			if (!temp_list)
				exit(1);
			temp_list[start -> count] = 0;
			cmd_count ++;
			cmd_list[cmd_count] = temp_list;
			token_count = 0;
		}
		else
			temp_list[token_count ++] = now;
		now = now -> next;
	}
}
