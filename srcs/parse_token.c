/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:23:00 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/11 12:58:54 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_char_from_idx(char *s, int idx)
{
	ft_memmove(&s[idx], &s[idx + 1], ft_strlen(s) - idx);
}

int	is_space(char c)
{
	if (c == ' ')
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

int	is_dollar_option(char *str)
{
	if (ft_strncmp(str, "$", 1) == 0)
		return (1);
	else if (ft_strncmp(str, "?", 1) == 0)
		return (1);
	return (0);
}

int	is_specifier(t_parse *parse)
{
	char	c;

	c = parse->s[parse->i];
	if (ft_strncmp(&parse->s[parse->i], "<<", 2) == 0 || \
		ft_strncmp(&parse->s[parse->i], ">>", 2) == 0)
	{
		return (2);
	}
	else if (c == '>' || c == '<' || c == '|')
	{
		return (1);
	}
	return (0);
}

int	is_backslash(t_parse *parse)
{
	if (parse->s[parse->i] == '\\')
		if (!parse->in_qout || (parse->in_qout && parse->q == '\"'))
			return (1);
	return (0);
}

char	*replace_dollar_to_env_sub(t_data *data, char *first, char* val, char *last)
{
	char	*ret;
	int	len;

	if (is_dollar_option(val))
	{
		if (ft_strncmp(val, "$", -1) == 0)
		{
			free(val);
			val = ft_itoa(getpid());
		}
		else if (ft_strncmp(val, "?", -1) == 0)
		{
			free(val);
			val = ft_itoa(data->exit_code);
		}
	}
	len = ft_strlen(first) + ft_strlen(val) + ft_strlen(last);
	ret = (char *)malloc(sizeof(char) * len + 1);
	ft_strlcpycpy(ret, first, ft_strlen(first) + 1);
	ft_strlcpycpy(&ret[ft_strlen(first)], val, ft_strlen(val) + 1);
	ft_strlcpycpy(&ret[ft_strlen(first) + ft_strlen(val)], last, len + 1);
	return (ret);
}

void	replace_dollar_to_env(t_data *data, t_parse *parse)
{
    t_env   *env;
	int	i;
	int	s;
    size_t buf_env_len;
	char	*buf_env;
    char    *buf_s;
    char    *buf_e;

	i = parse->i + 1;
	s = i;
	while (!is_space(parse->s[i]) && !is_quot(parse->s[i]) && \
			!is_dollar(parse->s[i]) && parse->s[i])
		i++;
	if (is_dollar(parse->s[parse->i + 1]))
		i++;
    buf_env_len = i - s + 1;
    buf_env = (char *)malloc(sizeof(char) * s + 1);
    buf_s = (char *)malloc(sizeof(char) * buf_env_len + 1);
    buf_e = (char *)malloc(sizeof(char) * ft_strlen(parse->s) + 1);
	ft_strlcpy(buf_s, parse->s, s);
	ft_strlcpy(buf_env, &parse->s[s], buf_env_len);
    ft_strlcpy(buf_e, &parse->s[i], ft_strlen(parse->s));
    env = search_env(data->env_list, buf_env);
    if (!env)
	{
		if (is_dollar_option(buf_env))
			parse->s = replace_dollar_to_env_sub(data, buf_s, buf_env, buf_e);
		else
			remove_char_from_idx(parse->s, parse->i);
	}
	else
		parse->s = replace_dollar_to_env_sub(data, buf_s, env->val, buf_e);
	free(buf_env);
    free(buf_s);
    free(buf_e);
}

int	valid_backslash(t_parse *parse)
{
	if (!parse->s[parse->i + 1])
		return (1);
	else
		return (0);
}

int	condition_specifier(t_parse *parse)
{
	if (is_specifier(parse))
	{
		parse->i += is_specifier(parse);
		parse->is_cmd = TRUE;
		return (1);
	}
	return (0);
}

int	condition_backslash(t_parse *parse)
{
	if (is_backslash(parse))
	{
		if (valid_backslash(parse))
		{
			parse->unclose_slash = TRUE;
			printf("unclose backslash\n");
			return (1);
		}
		remove_char_from_idx(parse->s, parse->i);
		parse->i++;
		return (2);
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
		parse->idxq_e = parse->i;
}

void	condition_dollar_exist(t_data *data, t_parse *parse)
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
		if (is_dollar(parse->s[parse->i + 1]))
			parse->i++;
	}
}

void	condition_qout_check(t_parse *parse)
{
	if (parse->in_qout && parse->idxq_e)
	{
		remove_char_from_idx(parse->s, parse->idxq_e);
		remove_char_from_idx(parse->s, parse->idxq_s);
		parse->in_qout = FALSE;
		parse->idxq_s = 0;
		parse->idxq_e = 0;
		parse->i -= 2;
	}
}

int	conditions(t_data *data, t_parse *parse)
{
	if (condition_specifier(parse))
		return (1);
	condition_qout_started(parse);
	condition_qout_ended(parse);
	condition_dollar_exist(data, parse);
	condition_qout_check(parse);
	if ((!parse->in_qout && is_space(parse->s[parse->i])) || \
		!parse->s[parse->i])
		return (1);
	return (0);
}

void	parse_token_sub(t_data *data, t_parse *parse)
{
	int	backslash_r;

	while (1)
	{
		backslash_r = is_backslash(parse);
		if (backslash_r == 1)
			break ;
		else if (backslash_r == 2)
			continue ;
		if (conditions(data, parse))
		{
			append_token(data->token_list, parse, &parse->s[parse->idx], \
						parse->i - parse->idx);
			parse->in_dollar = 0;
			parse->is_cmd = 0;
			break ;
		}
		parse->i++;
	}
}

void	init_parse(t_parse *parse, char *s)
{
	parse->s = s;
	parse->q = 0;
	parse->unclose_quot = FALSE;
	parse->unclose_slash = FALSE;
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

void	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(&parse, str);
	create_token_list(data);
	if (!is_space(parse.s[parse.i]))
	{
		parse.idx = parse.i;
		parse_token_sub(data, &parse);
	}
	while (parse.s[parse.i])
	{
		if (parse.s[parse.i + 1] && is_space(parse.s[parse.i]) \
			&& !is_space(parse.s[parse.i + 1]))
		{
			parse.i++;
			parse.idx = parse.i;
			parse_token_sub(data, &parse);
			parse.i--;
		}
		parse.i++;
	}
}