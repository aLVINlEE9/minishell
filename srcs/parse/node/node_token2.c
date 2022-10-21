/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:00:44 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:50 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_token_sub(t_token_list *list, t_token *new_node)
{
	list->tail->prev->next = new_node;
	new_node->prev = list->tail->prev;
	new_node->next = list->tail;
	list->tail->prev = new_node;
	list->count++;
}

int	append_token(t_token_list *list, t_parse *parse, char *token, size_t size)
{
	t_token		*new_node;
	char		*buf;

	if (parse->in_qout)
	{
		printf("unclose qout\n");
		return (0);
	}
	buf = (char *)malloc(sizeof(char) * size + 1);
	ft_strlcpy(buf, token, size + 1);
	new_node = 0;
	new_node = create_token(buf, parse);
	if (new_node == 0)
		return (1);
	append_token_sub(list, new_node);
	return (0);
}

t_token	*create_token(char *token, t_parse *parse)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (new_node == 0)
		return (0);
	new_node->token = token;
	new_node->in_dollar = parse->in_dollar;
	new_node->around = -1;
	new_node->is_cmd = parse->is_cmd;
	new_node->next = 0;
	new_node->prev = 0;
	return (new_node);
}
