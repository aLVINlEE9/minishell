/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:34:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/13 16:36:37 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	syntax_check(t_data *data)
{
	t_token	*now;

	now = data->token_list->head->next;
	while (now != data->token_list->tail)
	{
		
		now = now->next;
	}
}