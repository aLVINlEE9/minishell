/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:34:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 14:53:20 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	syntax_check_sub1(t_data *data, t_token *now)
{
	if (now->next == data->token_list->tail)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	else if (syntax_newline(now->next->token) || \
			syntax_pipe(now->next->token))
	{
		printf("syntax error near unexpected token `%s'\n", \
				now->next->token);
		return (1);
	}
	return (0);
}

int	syntax_check_sub2(t_data *data, t_token *now)
{
	if (now->next == data->token_list->tail)
	{
		printf("syntax error near unexpected token `%s'\n", \
				now->token);
		return (1);
	}
	else if (syntax_pipe(now->next->token))
	{
		printf("syntax error near unexpected token `%s'\n", \
				now->next->token);
		return (1);
	}
	return (0);
}

int	syntax_check_sub(t_data *data, t_token *now)
{
	if (now->is_cmd)
	{
		if (syntax_newline(now->token))
		{
			if (syntax_check_sub1(data, now))
				return (1);
		}
		else if (syntax_pipe(now->token))
		{
			if (syntax_check_sub2(data, now))
				return (1);
		}
	}
	return (0);
}

int	syntax_check(t_data *data)
{
	t_token	*now;

	now = data->token_list->head->next;
	if (now == data->token_list->tail)
		return (1);
	if (now->is_cmd && syntax_pipe(now->token))
	{
		printf("syntax error near unexpected token `%s'\n", now->token);
		return (1);
	}
	while (now != data->token_list->tail)
	{
		if (syntax_check_sub(data, now))
			return (1);
		now = now->next;
	}
	return (0);
}
