/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:10:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/09 17:20:31 by seungsle         ###   ########.fr       */
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

// void	replace_string(char *s, char *rep_s, int idx_s, int idx_e)
// {
// 	int	len;

// 	len = ft_strlen(rep_s);
// 	remove_string(s, idx_s, idx_e);
// 	if (len == 0)
// 		return ;
// 	else
// 	{
		
// 	}
// }

// void	replace_dollar(t_data *data, t_parse *parse)
// {
// 	t_env	*env;
// 	char	buf;

// 	if (parse->in_qout && parse->q == '\'')
// 		return ;
// 	else
// 	{
// 		ft_strlcpy(&buf, &parse->s[parse->idxd_s], parse->idxd_e - parse->idxd_e + 1);
// 		env = search_env(data->env_list, &buf);
// 		if (env == 0)
// 			replace_string(parse->s, "", parse->idxd_s - 1, parse->idxd_e);
// 		else
// 			replace_string(parse->s, env->val, parse->idxd_s - 1, parse->idxd_e);
// 	}
// }

int	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (is_backslash(parse->s, parse->i))
		{
			remove_char_from_idx(parse->s, parse->i);
			parse->i++;
			continue ;
		}
		if ((!parse->in_qout && is_space(parse->s[parse->i])) || !parse->s[parse->i])
		{
			append_token(data->token_list, parse, &parse->s[parse->idx], parse->i - parse->idx);
			parse->in_dollar = FALSE;
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
		else if (!parse->in_dollar && is_dollar(parse->s[parse->i]))
		{
			if (parse->in_qout && parse->q == '\'')
				parse->in_dollar = FALSE;
			else
				parse->in_dollar = TRUE;
		}
		// else if (parse->s[parse->i + 1] && parse->in_dollar && (is_space(parse->s[parse->i + 1]) || is_quot(parse->s[parse->i + 1])))
		// {
		// 	parse->idxd_e = parse->i;
		// 	replace_dollar(data, parse);
		// }
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