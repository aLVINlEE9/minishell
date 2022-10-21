/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:59:49 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 13:49:41 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		if (!val)
		{
			free(key);
			return (1);
		}
		if (!(val[0] == 0 && new_node->val))
		{
			new_node->val = val;
			new_node->is_val_quot = is_val_quot;
		}
	}
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
