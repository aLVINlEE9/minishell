/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_cmdlst2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:16:09 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 21:39:13 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	***make_t_cmd_make_lst(t_token_list *tok_lst, t_cmd_make **start, int cmd_count, int token_count)
{
	t_token		*now;
	t_cmd_make	*node;
	t_token		***cmd_list;

	now = tok_lst -> head -> next;
	while (now)
	{
		if ((now -> is_cmd == 1 && *(now -> token) == '|') || now == token_list -> tail)
		{
			(*cmd_count) ++;
			node = ft_lstnew(*token_count);
			ft_lstadd_back(start, node);
			(*token_count) = 0;
		}
		else
			(*token_count) ++;
		now = now -> next;
	}
	cmd_list = malloc(sizeof(struct s_token**) * (cmd_count + 1));
	if (!(cmd_list))
		exit(1); //error
	cmd_list[cmd_count] = 0;
	return (cmd_list);
}

/*t_token	**make_t_token_lst(t_cmd_make *start, )
{
	t_token	**temp_list;

	temp_list = malloc(sizeof(struct s_token*) * ((start -> count) + 1));
	if (!temp_list)
		exit(1);//error
	temp_list[start -> count] = 0;
	cmd_list[cmd_count] = temp_list;
}*/

void	whatisit(t_token_list *tok_lst, t_token ***cmd_list, t_cmd_make *start)
{
	t_token	*now;
	int	token_count;
	int	cmd_count;
	t_cmd_make	*temp;

	temp = start;
	token_count = 0;
	cmd_count = 0;
	now = tok_lst -> head -> next;
	while (now != token_list -> tail)
	{
		if (now -> is_cmd  == 1 && *(now -> token) == '|')
		{
			temp = temp -> next;
			temp_list = malloc(sizeof(struct s_token) * ((temp -> count) + 1));
			if (!temp_list)
				exit(1);//error
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
}
