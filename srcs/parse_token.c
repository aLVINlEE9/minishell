/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:37:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/07 15:55:23 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_dollar(char c)
{
	if (c == '$')
		return(1);
	return (0);
}

int is_dquot(char c)
{
	if (c == '\"')
		return (1);
	return (0);
}

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

void    parse_token(t_data *data, char *str)
{
	char    *s;
	char    *buf_q;
	char    *buf_s;
	int     dollar;

	s = str;
	buf_q = s;
	buf_s = s;
	dollar = 0;
	create_token_list(data);
	if (!is_quot(*s) && !is_space(*s))
	{
		buf_s = s;
		while (*buf_s)
		{
			if (is_space(*buf_s))
			{
				append_token(data->token_list, s, buf_s - s);
				break ;
			}
			buf_s++;
		}
		s = buf_s - 1;
	}
	while (*(s))
	{
		if (is_quot(*s))
		{
			buf_q = s;
			buf_q++;
			while(*buf_q)
			{
				if (*s == *buf_q)
				{
					if (*(buf_q - 1) == '\\' && *(buf_q - 2) != '\\')
						buf_q++;
					append_token(data->token_list, s + 1, buf_q - s - 1);
					break ;
				}
				buf_q++;
			}
			s = buf_q;
		}
		if (is_space(*s) && *(s + 1) && !is_space(*(s + 1)) && !is_quot(*(s + 1)))
		{
			s++;
			buf_s = s;
			while (*buf_s)
			{
				if (is_space(*buf_s) || *(buf_s + 1) == 0)
				{
					if (*(buf_s + 1) == 0)
						buf_s++;
					append_token(data->token_list, s, buf_s - s);
					break ;
				}
				buf_s++;
			}
			s = buf_s - 1;
		}
		s++;
	}
	if ((str && !*buf_q)) // quotation only once
	{
		printf("quotation only once\n");
	}
}