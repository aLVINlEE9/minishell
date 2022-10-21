/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:35:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 16:23:09 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_null(char c)
{
	if (c == '\0')
		return (1);
	return (0);
}

int	is_quot(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
