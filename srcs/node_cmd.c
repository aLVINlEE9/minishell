/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 22:57:06 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/06 23:31:45 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*search_cmd(t_cmd_list *list, char *cmd)
{
    t_cmd   *now;

    now = list->head->next;
    while (now)
    {
        if (ft_strncmp(now->cmd, cmd, -1) == 0)
            return (now);
        now = now->next;
    }
    return (NULL);
}

int	create_cmd_list_sub(t_cmd_list *list)
{
	t_cmd	*head;
	t_cmd	*tail;

	list->head = (t_cmd *)malloc(sizeof(t_cmd));
	if (list->head == NULL)
		return (1);
	list->tail = (t_cmd *)malloc(sizeof(t_cmd));
	if (list->tail == NULL)
		return (1);
	head = list->head;
	tail = list->tail;
	head->cmd = NULL;
	head->dollar = 0;
	tail->cmd = NULL;
	tail->dollar = 0;
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
	tail->prev = head;
	return (0);
}

void	create_cmd_list(t_data *data)
{
	data->cmd_list = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (data->cmd_list == NULL)
		exit(1);
	if (create_cmd_list_sub(data->cmd_list))
		exit(1);
	data->cmd_list->count = 0;
}


void	append_cmd_sub(t_cmd_list *list, t_cmd *new_node)
{
	list->tail->prev->next = new_node;
	new_node->prev = list->tail->prev;
	new_node->next = list->tail;
	list->tail->prev = new_node;
	list->count++;
}

int	append_cmd(t_cmd_list *list, char *cmd, size_t size, int dollar)
{
	t_cmd		*new_node;
	char		buf;

	ft_strlcpy(&buf, cmd, size);
	new_node = NULL;
	new_node = create_cmd(buf, dollar);
	if (new_node == NULL)
		return (1);
	append_cmd_sub(list, new_node);
	return (0);
}

t_cmd	*create_cmd(char *cmd, int dollar)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_node == NULL)
		return (NULL);
	new_node->cmd = cmd;
	new_node->dollar = dollar;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
