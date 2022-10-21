/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_cmdlst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:12:56 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:17 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_cmd_make **lst, t_cmd_make *new)
{
	t_cmd_make	*iter;

	iter = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		new -> next = NULL;
	}
	else
	{
		while (iter -> next != NULL)
			iter = iter -> next;
		iter -> next = new;
		new -> next = NULL;
	}
	return ;
}

t_cmd_make	*ft_lstnew(int c)
{
	t_cmd_make	*p;

	p = malloc(sizeof(t_cmd_make) * 1);
	if (!p)
		return (0);
		p -> count = c;
	p -> next = NULL;
	return (p);
}

void	free_cmdmake(t_cmd_make **lst)
{
	t_cmd_make	*temp;
	t_cmd_make	*save;

	temp = (*lst);
	if (!(*lst))
		return ;
	save = temp -> next;
	free(temp);
	while (save)
	{
		temp = save;
		save = save -> next;
		free(temp);
	}
	return ;
}

void	free_cmdlst(t_token ***lst)
{
	int	count;

	count = 0;
	while (lst[count])
	{
		free(lst[count]);
		count ++;
	}
	free(lst);
}
