/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/06 19:14:59 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*search_env(t_env_list *list, char *key)
{
    t_env   *now;

    now = list->head->next;
    while (now)
    {
        if (ft_strncmp(now->key, key, -1) == 0)
            return (now);
        now = now->next;
    }
    return (NULL);
}

int	create_env_list_sub(t_env_list *list)
{
	t_env	*head;
	t_env	*tail;

	list->head = (t_env *)malloc(sizeof(t_env));
	if (list->head == NULL)
		return (1);
	list->tail = (t_env *)malloc(sizeof(t_env));
	if (list->tail == NULL)
		return (1);
	head = list->head;
	tail = list->tail;
	head->key = NULL;
	head->val = NULL;
	tail->key = NULL;
	tail->val = NULL;
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = head;
	return (0);
}

void	create_env_list(t_data *data)
{
	data->env_list = (t_env_list *)malloc(sizeof(t_env_list));
	if (data->env_list == NULL)
		exit(1);
	if (create_env_list_sub(data->env_list))
		exit(1);
	data->env_list->count = 0;
}


void	append_env_sub(t_env_list *list, t_env *new_node)
{
	list->tail->prev->next = new_node;
	new_node->prev = list->tail->prev;
	new_node->next = list->tail;
	list->tail->prev = new_node;
	list->count++;
}

int	append_env(t_env_list *list, char *key, char *val)
{
	t_env		*new_node;

	new_node = NULL;
	new_node = create_env(key, val);
	if (new_node == NULL)
		return (1);
	append_env_sub(list, new_node);
	return (0);
}

t_env	*create_env(char *key, char *val)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
		return (NULL);
	new_node->key = key;
	new_node->val = val;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
