/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:10:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/08 18:15:53 by seungsle         ###   ########.fr       */
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

int	is_string(char c)
{
	if (!is_space(c) && !is_quot(c))
		return (1);
	return (0);
}

char	quot_after_string(char *str, int i)
{
	if (str[i + 1] && is_string(str[i]) && is_quot(str[i + 1]))
		return (str[i + 1]);
	return (0);
}

int	string_after_quot(char *str, int i, char q)
{
	if (str[i + 1] && (str[i] == q) && is_string(str[i + 1]))
		return (1);
	return (0);
}

int	is_backslash(char *str, int i)
{
	if (!str[i + 1])
		return (0);
	if (str[i] == '\\')
	{
		if (str[i + 1] == '\"')
			return (1);
		else if (str[i + 1] == '\\')
			return (1);
	}
	return (0);
}

void	parse_token(t_data *data, char *str)
{
	char	*s;
	char	q;
	int	i;
	int	in_qout;
	int	idx;
	int	idxq_s;
	int	idxq_e;

	s = str;
	i = 0;
	in_qout = FALSE;
	idx = 0;
	idxq_s = 0;
	idxq_e = 0;
	create_token_list(data);
	if (!is_space(s[i]))
	{
		idx = i;
		while (1)
		{
			if (is_backslash(s, i))
			{
				ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
				i++;
				continue ;
			}
			if ((!in_qout && is_space(s[i])) || !s[i])
			{
				append_token(data->token_list, &s[idx], i - idx);
				break ;
			}
			else if (!in_qout && is_quot(s[i]))
			{
				in_qout = TRUE;
				idxq_s = i;
				q = s[i];
			}
			else if (in_qout && q == s[i])
			{
				idxq_e = i;
			}
			if (in_qout && idxq_s && idxq_e)
			{
				ft_memmove(&s[idxq_e], &s[idxq_e + 1], ft_strlen(s) - idxq_e);
				ft_memmove(&s[idxq_s], &s[idxq_s + 1], ft_strlen(s) - idxq_s);
				in_qout = FALSE;
				idxq_s = 0;
				idxq_e = 0;
				i -= 2;
			}
			i++;
		}
	}
	while (s[i])
	{
		if (s[i] && is_space(s[i]) && !is_space(s[i + 1]))
		{
			i++;
			idx = i;
			while (1)
			{
				if (is_backslash(s, i))
				{
					ft_memmove(&s[i], &s[i + 1], ft_strlen(s) - i);
					i++;
					continue ;
				}
				if ((!in_qout && is_space(s[i])) || !s[i])
				{
					append_token(data->token_list, &s[idx], i - idx);
					break ;
				}
				else if (!in_qout && is_quot(s[i]))
				{
					in_qout = TRUE;
					idxq_s = i;
					q = s[i];
				}
				else if (in_qout && q == s[i])
				{
					idxq_e = i;
				}
				if (in_qout && idxq_s && idxq_e)
				{
					ft_memmove(&s[idxq_e], &s[idxq_e + 1], ft_strlen(s) - idxq_e);
					ft_memmove(&s[idxq_s], &s[idxq_s + 1], ft_strlen(s) - idxq_s);
					in_qout = FALSE;
					idxq_s = 0;
					idxq_e = 0;
					i -= 2;
				}
				i++;
			}
			i--;
		}
		i++;
	}
}

// inside quot => ignore space
// else => check space