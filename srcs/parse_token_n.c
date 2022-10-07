/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:10:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/07 19:36:47 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_quot(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

char	*trim_space(char *s)
{
	char	q;
	char	*ret;
	char	*buf;

	buf = s;
	ret = s;
	while (*buf)
	{
		if (*(buf + 1) && !is_space(*buf) && is_quot(*(buf + 1)))
		{
			q = *buf;
			buf += 2;
			while (*buf != q)
			{
				*ret = *buf;
				buf++;
				ret++;
			}
			buf++;
		}
		*ret = *buf;
		buf++;
		ret++;
	}
	*ret = 0;
	return (s);
}

void	parse_token(t_data *data, char *str)
{
	char	*s;

	s = str;
	create_token_list(data);
	s = trim_space(s);
	printf("%s\n", s);
	// while (*s)
	// {
	// 	s++;
	// }
}