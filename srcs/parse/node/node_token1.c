/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_token1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:29:41 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 12:01:52 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_token	*search_token(t_token_list *list, char *token)
{
    t_token   *now;

    now = list->head->next;
    while (now != list->tail)
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
