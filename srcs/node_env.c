/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:24:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/19 17:49:27 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


void	append_env_sub(t_env_list *list, t_env *new_node)
{
	list->tail->prev->next = new_node;
	new_node->prev = list->tail->prev;
	new_node->next = list->tail;
	list->tail->prev = new_node;
	list->count++;
}

int	append_env(t_env_list *list, char *key, char *val, int is_val_quot)
{
	t_env		*new_node;

	new_node = search_env(list, key);
	if (!new_node)
	{
		new_node = create_env(key, val, is_val_quot);
		if (new_node == 0)
			return (1);
		append_env_sub(list, new_node);
	}
	else
	{
		printf("%d %s\n", val[0] == 0, new_node->val);
		if (!(val[0] == 0 && new_node->val))
		{
			new_node->val = val;
			new_node->is_val_quot = is_val_quot;
		}
	}
	// print_env(list);
	return (0);
}

t_env	*create_env(char *key, char *val, int is_val_quot)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == 0)
		return (0);
	new_node->key = key;
	new_node->val = val;
	new_node->next = 0;
	new_node->prev = 0;
    new_node->is_val_quot = is_val_quot;
	return (new_node);
}
