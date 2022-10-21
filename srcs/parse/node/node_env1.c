/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 12:01:42 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*search_env(t_env_list *list, char *key)
{
    t_env   *now;

    if (is_dollar_option(key))
        return (0);
    now = list->head->next;
    while (now != list->tail)
    {
        if (ft_strncmp(now->key, key, -1) == 0)
            return (now);
        now = now->next;
    }
    return (0);
}

int	create_env_list_sub(t_env_list *list)
{
	t_env	*head;
	t_env	*tail;

	list->head = (t_env *)malloc(sizeof(t_env));
	if (list->head == 0)
		return (1);
	list->tail = (t_env *)malloc(sizeof(t_env));
	if (list->tail == 0)
		return (1);
	head = list->head;
	tail = list->tail;
	head->key = 0;
	head->val = 0;
	tail->key = 0;
	tail->val = 0;
	head->next = tail;
	head->prev = 0;
	tail->next = 0;
	tail->prev = head;
	return (0);
}

void	create_env_list(t_data *data)
{
	data->env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (data->env_list == 0)
		exit(1);
	if (create_env_list_sub(data->env_list))
		exit(1);
	data->env_list->count = 0;
}
