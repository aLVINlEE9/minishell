/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:10:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/10 00:40:15 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quot(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	condition_backslash(t_parse *parse)
{
	if (parse->s[parse->i] == '\\')
		if (!parse->in_qout || (parse->in_qout && parse->q == '\"'))
			return (1);
	return (0);
}

int	valid_backslash(t_parse *parse)
{
	if (!parse->s[parse->i + 1])
		return (1);
	else
		return (0);
}

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

void	remove_char_from_idx(char *s, int idx)
{
	ft_memmove(&s[idx], &s[idx + 1], ft_strlen(s) - idx);
}

void	remove_string(char *s, int idx_s, int idx_e)
{
	while (idx_s <= idx_e)
	{
		remove_char_from_idx(s, idx_e);
		idx_e--;
	}
}

int	condition_append_token(t_parse *parse)
{
	if ((!parse->in_qout && is_space(parse->s[parse->i])) || \
			!parse->s[parse->i])
		return (1);
	return (0);
}

int	condition_qout_started(t_parse *parse)
{
	if (!parse->in_qout && is_quot(parse->s[parse->i]))
		return (1);
	return (0);
}

int	condition_qout_ended(t_parse *parse)
{
	if (parse->in_qout && parse->q == parse->s[parse->i])
		return (1);
	return (0);
}

int	condition_dollar_exist(t_parse *parse)
{
	if (is_dollar(parse->s[parse->i]) && !is_quot(parse->s[parse->i + 1]) \
			&& !is_space(parse->s[parse->i + 1]) && parse->s[parse->i + 1])
		return (1);
	return (0);
}

void	replace_dollar_to_env_sub(t_data *data, t_parse *parse, char *key)
{
	t_env	*env;

	env = search_env(data->env_list, key);
	if (!env)
		return ;
	env->val;
}

void	replace_dollar_to_env(t_data *data, t_parse *parse)
{
	int	i;
	int	s;
	int	e;
	char	buf;
	char	*ret;
	char	*splited;

	i = parse->i;
	s = i;
	while (!is_space(parse->s[i]) && !is_quot(parse->s[i]) && \
			!is_dollar(parse->s[i]))
		i++;
	e = i;
	ft_strlcpy(&buf, &parse->s[s], e - s + 1);
	ret = ft_strdup(&buf);
	replace_dollar_to_env_sub(data, parse, ret);
}

int	parse_condition_check(t_data *data, t_parse *parse)
{
	if (condition_append_token(parse))
	{
		append_token(data->token_list, parse, &parse->s[parse->idx], \
						parse->i - parse->idx);
		parse->in_dollar = 0;
		return (1);
	}
	else if (condition_qout_started(parse))
	{
		parse->in_qout = TRUE;
		parse->idxq_s = parse->i;
		parse->q = parse->s[parse->i];
	}
	else if (condition_qout_ended(parse))
		parse->idxq_e = parse->i;
	else if (condition_dollar_exist(parse))
	{
		if (!(parse->in_qout && parse->q == '\''))
		{
			parse->in_dollar++;
			replace_dollar_to_env(data, parse);
			if (is_dollar(parse->s[parse->i + 1]))
				parse->i++;
		}
	}
	return (0);
}

int	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (condition_backslash(parse))
		{
			if (valid_backslash(parse))
			{
				printf("unclose backslash\n");
				break ;
			}
			remove_char_from_idx(parse->s, parse->i);
			parse->i++;
			continue ;
		}
		if (parse_condition_check(data, parse))
			break ;
		if (parse->in_qout && parse->idxq_e)
		{
			remove_char_from_idx(parse->s, parse->idxq_e);
			remove_char_from_idx(parse->s, parse->idxq_s);
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
	parse->in_dollar = FALSE;
	parse->idx = 0;
	parse->idxq_s = 0;
	parse->idxq_e = 0;
	parse->idxd_s = 0;
	parse->idxd_e = 0;
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
		if (parse.s[parse.i] && parse.s[parse.i + 1] && \
			is_space(parse.s[parse.i]) && !is_space(parse.s[parse.i + 1]))
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