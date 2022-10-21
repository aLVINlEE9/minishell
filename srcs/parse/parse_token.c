/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:23:00 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 11:38:26 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_parse(t_parse *parse, char *str)
{
	parse->s = str;
	parse->q = 0;
	parse->i = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
	parse->idx = 0;
	parse->is_cmd = 0;
	parse->is_env = 0;
	parse->idxq_s = 0;
	parse->idxq_e = 0;
	parse->idxd_s = 0;
	parse->idxd_e = 0;
}

void	init_parse_sub(t_parse *parse)
{
	parse->is_cmd = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
	parse->is_env = FALSE;
	parse->was_quot = FALSE;
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

void	qout_remove(t_parse *parse)
{
	if (parse->in_qout && parse->idxq_e)
	{
		remove_char_from_idx(parse->s, parse->idxq_e);
		remove_char_from_idx(parse->s, parse->idxq_s);
		parse->in_qout = FALSE;
		parse->idxq_s = 0;
		parse->idxq_e = 0;
		parse->i -= 2;
		parse->was_quot = TRUE;
	}
}

void	replace_util_sub(t_parse *parse, char *first, char *val, char *last)
{
	char	*ret;
	int		len;

	len = ft_strlen(first) + ft_strlen(val) + ft_strlen(last);
	ret = (char *)malloc(sizeof(char) * len + 1);
	if (!ret)
		return ;
	ft_strlcpycpy(ret, first, ft_strlen(first) + 1);
	ft_strlcpycpy(&ret[ft_strlen(first)], val, ft_strlen(val) + 1);
	ft_strlcpy(&ret[ft_strlen(first) + ft_strlen(val)], last, len + 1);
	parse->s = ret;
}

void	replace_dollar_options(t_data *data, t_parse *parse, char *buf_start, char *buf_end)
{
	char	*val;

	val = 0;
	if (is_dollar_option(&parse->s[parse->i]) == 2)
		val = ft_itoa(getpid());
	else if (is_dollar_option(&parse->s[parse->i]) == 1)
		val = ft_itoa(data->exit_code);
	remove_char_from_idx(parse->s, parse->i);
	replace_util_sub(parse, buf_start, val, buf_end);
	parse->is_env = TRUE;
}

void	replace_util(t_data *data, t_parse *parse, int idx, int start)
{
	t_env	*env;
	size_t	buf_env_len;
	char	*buf_start;
	char	*buf_env;
	char	*buf_end;

	buf_env_len = idx - start + 1;
	buf_start = (char *)malloc(sizeof(char) * start + 1);
	buf_env = (char *)malloc(sizeof(char) * buf_env_len);
	buf_end = (char *)malloc(sizeof(char) * ft_strlen(parse->s) - idx + 1);
	ft_strlcpy(buf_start, parse->s, start);
	ft_strlcpy(buf_env, &parse->s[start], buf_env_len);
	ft_strlcpy(buf_end, &parse->s[idx], ft_strlen(parse->s) - idx + 1);
	if (is_dollar_option(&parse->s[parse->i]))
		replace_dollar_options(data, parse, buf_start, buf_end);
	else
	{
		env = search_env(data->env_list, buf_env);
		if (!env)
		{
			remove_string(parse->s, parse->i, parse->i + buf_env_len - 1);
			parse->is_env = FALSE;
			// if (!parse->in_qout)
			parse->i--;
		}
		else
		{
			replace_util_sub(parse, buf_start, env->val, buf_end);
			parse->is_env = TRUE;
		}
	}
	free(buf_start);
	free(buf_env);
	free(buf_end);
}

void	replace_dollar_to_env(t_data *data, t_parse *parse)
{
	int	idx;
	int	start;

	idx = parse->i + 1;
	start = idx;
	if (is_dollar_option(&parse->s[parse->i]))
		idx++;
	else
	{
		if (!is_alpha(parse->s[start]) && parse->s[start] != '_')
		{
			if (is_num(parse->s[start]))
				replace_util(data, parse, idx + 1, start);
			return ;
		}
		while (!is_space(parse->s[idx]) && !is_quot(parse->s[idx]) && \
			!is_dollar(parse->s[idx]) && parse->s[idx] && \
			(is_alnum(parse->s[idx]) || parse->s[idx] == '_'))
		idx++;
	}
	replace_util(data, parse, idx, start);
}

void	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (condition_break(parse))
			break ;
		if (condition_append_token(parse))
		{
			append_token(data->token_list, parse, &parse->s[parse->idx], \
						parse->i - parse->idx);
			break ;
		}
		condition_qout(parse);
		condition_dollar(data, parse);
		parse->i++;
	}
}

int	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(&parse, str);
	create_token_list(data);
	while(parse.s[parse.i])
	{
		parse.idx = parse.i;
		init_parse_sub(&parse);
		if (!is_space(parse.s[parse.i]))
			parse_token_sub(data, &parse);
		if (is_space(parse.s[parse.i]))
			parse.i++;
	}
	if (syntax_check(data))
        return (0);
    return (1);
}