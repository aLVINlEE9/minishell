/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:29:41 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/10 16:13:14 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

t_token	*search_token(t_token_list *list, char *token)
{
    t_token   *now;

    now = list->head->next;
    while (now)
    {
        if (ft_strncmp(now->token, token, -1) == 0)
            return (now);
        now = now->next;
    }
    return (0);
}

int	create_token_list_sub(t_token_list *list)
{
	t_token	*head;
	t_token	*tail;

	list->head = (t_token *)malloc(sizeof(t_token));
	if (list->head == 0)
		return (1);
	list->tail = (t_token *)malloc(sizeof(t_token));
	if (list->tail == 0)
		return (1);
	head = list->head;
	tail = list->tail;
	head->token = 0;
	head->in_dollar = 0;
	head->around = -1;
	tail->token = 0;
	tail->in_dollar = 0;
	tail->around = -1;
	head->next = tail;
	head->prev = 0;
	tail->next = 0;
	tail->prev = head;
	return (0);
}

void	create_token_list(t_data *data)
{
	data->token_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (data->token_list == 0)
		exit(1);
	if (create_token_list_sub(data->token_list))
		exit(1);
	data->token_list->count = 0;
}


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
	char		buf;
	char		*ret;

	if (parse->in_qout)
	{
		printf("unclose qout\n");
		return (0);
	}
	ft_strlcpy(&buf, token, size + 1);
	ret = ft_strdup(&buf);
	new_node = 0;
	new_node = create_token(ret, parse);
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
