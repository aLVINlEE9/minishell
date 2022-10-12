/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:23:00 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/12 16:39:54 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_quot(char c)
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

int	is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

int	is_dollar_option(char *str)
{
	if (ft_strncmp(str, "$$", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "$?", 2) == 0)
		return (2);
	return (0);
}

int	is_specifier(t_parse *parse, int check)
{
	char	c;

	c = parse->s[parse->i + check];
	if (ft_strncmp(&parse->s[parse->i + check], "<<", 2) == 0 || \
		ft_strncmp(&parse->s[parse->i + check], ">>", 2) == 0)
	{
		return (2);
	}
	else if (c == '>' || c == '<' || c == '|')
	{
		return (1);
	}
	return (0);
}

void	remove_char_from_idx(char *s, int idx)
{
	ft_memmove(&s[idx], &s[idx + 1], ft_strlen(s) - idx);
}

int	condition_specifier(t_parse *parse, int check)
{
	if (is_specifier(parse, check) == 1 || is_specifier(parse, check) == 2)
	{
		parse->is_cmd = TRUE;
		return (1);
	}
}

void	init_parse_sub(t_parse *parse)
{
	parse->is_cmd = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
}

void	init_parse(t_parse *parse, char *str)
{
	parse->s = str;
	parse->q = 0;
	parse->i = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
	parse->idx = 0;
	parse->is_cmd = 0;
	parse->idxq_s = 0;
	parse->idxq_e = 0;
	parse->idxd_s = 0;
	parse->idxd_e = 0;
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
	ft_strlcpycpy(&ret[ft_strlen(first) + ft_strlen(val)], last, len + 1);
	free(parse->s);
	parse->s = ret;
}

void	replace_util(t_parse *parse, int idx, int start)
{
	size_t	buf_env_len;
	char	*buf_start;
	char	*buf_env;
	char	*buf_end;

	buf_env_len = idx - start + 1;
	buf_start = (char *)malloc(sizeof(char) * start - 1);
	buf_env = (char *)malloc(sizeof(char) * buf_env_len);
	buf_end = (char *)malloc(sizeof(char) * ft_strlen(parse->s) - idx + 1);
	ft_strlcpy(buf_start, parse->s, start - 2);
	ft_strlcpy(buf_env, &parse->s[start], buf_env_len - 1);
	ft_strlcpy(buf_end, &parse->s[idx], ft_strlen(parse->s) - idx);
	
}

void	replace_dollar_options(t_data *data, t_parse *parse)
{
	char	*val;

	if (is_dollar_option(parse->s) == 1)
		val = ft_itoa(getpid());
	else if (is_dollar_option(parse->s == 2))
		val = ft_itoa(data->exit_code);
	
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
		while (!is_space(parse->s[idx]) && !is_quot(parse->s[idx]) && \
			!is_dollar(parse->s[idx]) && parse->s[idx])
		idx++;
	}
	replace_util(parse, idx, start);
}

int	condition_append_token(t_parse *parse)
{
	if (parse->is_cmd == TRUE)
	{
		parse->i += is_specifier(parse, 0); // just cmd
		return (1);
	}
	else if (!parse->s[parse->i]) // null before
	{
		return (1);
	}
	else if (!parse->in_qout && is_space(parse->s[parse->i])) // space before
	{
		return (1);
	}
	else if (!parse->in_qout && is_specifier(parse, 0)) // cmd before
	{
		return (1);
	}
	return (0);
}

void	condition_qout_started(t_parse *parse)
{
	if (!parse->in_qout && is_quot(parse->s[parse->i]))
	{
		parse->in_qout = TRUE;
		parse->idxq_s = parse->i;
		parse->q = parse->s[parse->i];
	}
}

void	condition_qout_ended(t_parse *parse)
{
	if (parse->in_qout && parse->q == parse->s[parse->i])
	{
		parse->idxq_e = parse->i;
	}
}

void	condition_dollar(t_data *data, t_parse *parse)
{
	if (is_dollar(parse->s[parse->i]) && parse->s[parse->i + 1] && \
		!is_space(parse->s[parse->i + 1]))
	{
		if (is_quot(parse->s[parse->i + 1]))
		{
			remove_char_from_idx(parse->s, parse->i);
			parse->i--;
		}
		else if (!(parse->in_qout && parse->q == '\''))
		{
			parse->in_dollar++;
			replace_dollar_to_env(data, parse);
		}
	}
}

void	condition_backslash(t_parse *parse)
{
	
}

void	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (condition_append_token(parse))
		{
			append_token(data->token_list, parse, &parse->s[parse->idx], \
						parse->i - parse->idx);
			break ;
		}
		condition_dollar(data, parse);
		condition_backslash(parse);
		condition_qout_started(parse);
		condition_qout_ended(parse);
		parse->i++;
	}
}

void	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(&parse, str);
	if (!is_space(parse.s[parse.i]) || condition_specifier(&parse, 0))
	{
		parse.idx = parse.i;
		parse_token_sub(data, &parse);
	}
	while (parse.s[parse.i])
	{
		init_parse_sub(&parse);
		parse.idx = parse.i;
		if ((parse.s[parse.i + 1] && is_space(parse.s[parse.i]) \
			&& !is_space(parse.s[parse.i + 1]))) // word after space
		{
			condition_specifier(&parse, 1);
			parse_token_sub(data, &parse);
		}
		else if (condition_specifier(&parse, 0)) // now cmd
		{
			parse_token_sub(data, &parse);
		}
		else if (parse.s[parse.i] && !is_space(parse.s[parse.i]) && \
				is_specifier(&parse, -1)) // after cmd with no space
		{
			parse_token_sub(data, &parse);
		}
		parse.i++;
	}
}