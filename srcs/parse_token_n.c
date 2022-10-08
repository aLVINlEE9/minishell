/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:10:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/08 19:10:53 by seungsle         ###   ########.fr       */
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

int	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (is_backslash(parse->s, parse->i))
		{
			ft_memmove(&parse->s[parse->i], &parse->s[parse->i + 1], ft_strlen(parse->s) - parse->i);
			parse->i++;
			continue ;
		}
		if ((!parse->in_qout && is_space(parse->s[parse->i])) || !parse->s[parse->i])
		{
			append_token(data->token_list, &parse->s[parse->idx], parse->i - parse->idx);
			break ;
		}
		else if (!parse->in_qout && is_quot(parse->s[parse->i]))
		{
			parse->in_qout = TRUE;
			parse->idxq_s = parse->i;
			parse->q = parse->s[parse->i];
		}
		else if (parse->in_qout && parse->q == parse->s[parse->i])
		{
			parse->idxq_e = parse->i;
		}
		if (parse->in_qout && parse->idxq_e)
		{
			ft_memmove(&parse->s[parse->idxq_e], &parse->s[parse->idxq_e + 1], ft_strlen(parse->s) - parse->idxq_e);
			ft_memmove(&parse->s[parse->idxq_s], &parse->s[parse->idxq_s + 1], ft_strlen(parse->s) - parse->idxq_s);
			parse->in_qout = FALSE;
			parse->idxq_s = 0;
			parse->idxq_e = 0;
			parse->i -= 2;
		}
		parse->i++;
	}
	return (parse->i);
}

void	init_parse(t_parse *parse, char *str)
{
	parse->s = str;
	parse->q = 0;
	parse->i = 0;
	parse->in_qout = FALSE;
	parse->idx = 0;
	parse->idxq_s = 0;
	parse->idxq_e = 0;
}

void	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(&parse, str);
	create_token_list(data);
	if (!is_space(parse.s[parse.i]))
	{
		parse.idx = parse.i;
		parse.i = parse_token_sub(data, &parse);
	}
	while (parse.s[parse.i])
	{
		if (parse.s[parse.i] && parse.s[parse.i + 1] && is_space(parse.s[parse.i]) && !is_space(parse.s[parse.i + 1]))
		{
			parse.i++;
			parse.idx = parse.i;
			parse.i = parse_token_sub(data, &parse);
			parse.i--;
		}
		parse.i++;
	}
}

// inside quot => ignore space
// else => check space