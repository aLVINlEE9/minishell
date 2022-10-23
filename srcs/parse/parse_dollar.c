/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:56:58 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 14:33:58 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_util_sub1(t_parse *parse, char *first, char *val, char *last)
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
	free(parse->s);
	parse->s = ret;
}

void	replace_util_sub2(t_parse *parse, char *buf_start, char *buf_env, \
						char *buf_end)
{
	t_env	*env;

	env = search_env(parse->data->env_list, buf_env);
	if (!env)
	{
		remove_string(parse->s, parse->i, parse->i + parse->buf_env_len - 1);
		parse->is_env = FALSE;
		parse->i--;
	}
	else
	{
		replace_util_sub1(parse, buf_start, env->val, buf_end);
		parse->is_env = TRUE;
	}
}

void	replace_dollar_options(t_data *data, t_parse *parse, char *buf_start, \
								char *buf_end)
{
	char	*val;

	val = 0;
	if (is_dollar_option(&parse->s[parse->i]) == 2)
		val = ft_itoa(getpid());
	else if (is_dollar_option(&parse->s[parse->i]) == 1)
		val = ft_itoa(data->exit_code);
	remove_char_from_idx(parse->s, parse->i);
	replace_util_sub1(parse, buf_start, val, buf_end);
	free(val);
	parse->is_dollar_option = TRUE;
	parse->is_env = TRUE;
}

void	replace_util(t_data *data, t_parse *parse, int idx, int start)
{
	size_t	buf_env_len;
	char	*buf_start;
	char	*buf_env;
	char	*buf_end;

	parse->buf_env_len = idx - start + 1;
	buf_start = (char *)malloc(sizeof(char) * start + 1);
	buf_env = (char *)malloc(sizeof(char) * parse->buf_env_len);
	buf_end = (char *)malloc(sizeof(char) * ft_strlen(parse->s) - idx + 1);
	ft_strlcpy(buf_start, parse->s, start);
	ft_strlcpy(buf_env, &parse->s[start], parse->buf_env_len);
	ft_strlcpy(buf_end, &parse->s[idx], ft_strlen(parse->s) - idx + 1);
	if (is_dollar_option(&parse->s[parse->i]))
		replace_dollar_options(data, parse, buf_start, buf_end);
	else
		replace_util_sub2(parse, buf_start, buf_env, buf_end);
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
