/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:27:50 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/14 15:12:49 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int is_quot(char c)
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

int	is_dollar_option(char *str)
{
	if (ft_strncmp(str, "$$", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "$?", 2) == 0)
		return (2);
	return (0);
}

int	is_end(t_parse *parse)
{
	if (!parse->in_qout)
	{
		if (!parse->s[parse->i + 1])
			return (1);
		else if (parse->s[parse->i + 1] && (is_space(parse->s[parse->i + 1]) || \
				is_specifier(parse, 1)))
			return (2);
	}
	return (0);
}

int	check_next_idx(t_parse *parse)
{
	if (!parse->s[parse->i + 1])
		return (1);
	else
		return (0);
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
}

void	remove_char_from_idx(char *s, int idx)
{
	ft_memmove(&s[idx], &s[idx + 1], ft_strlen(s) - idx);
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
	}
}

void	replace_dollar_to_env(t_data *data, t_parse *parse)
{
	
}

int	condition_backslash(t_parse *parse)
{
	if (parse->s[parse->i] == '\\' && !is_end(parse))
	{
		if (!parse->in_qout || (parse->in_qout && parse->q == '\"'))
		{
			if (check_next_idx(parse))
			{
				printf("unclose backslash");
				parse->unclose_slash = TRUE;
				exit(1);
			}
			remove_char_from_idx(parse->s, parse->i);
			parse->i++;
			return (1);
		}
	}
	return (0);
}

void	condition_qout(t_parse *parse)
{
	if (!parse->in_qout && is_quot(parse->s[parse->i]))
	{
		parse->in_qout = TRUE;
		parse->idxq_s = parse->i;
		parse->q = parse->s[parse->i];
	}
	else if (parse->in_qout && parse->q == parse->s[parse->i])
	{
		parse->idxq_e = parse->i;
	}
	qout_remove(parse);
}

void	condition_dollar(t_data *data, t_parse *parse)
{
	if (is_dollar(parse->s[parse->i]) && !is_end(parse))
	{
		if (!parse->in_qout && is_quot(parse->s[parse->i + 1]))
		{
			remove_char_from_idx(parse->s, parse->i);
			parse->i--;
		}
		else if (!(parse->in_qout && parse->q == '\''))
		{
			parse->in_dollar++;
			replace_dollar_to_env(data, parse);
			if (is_dollar_option(&parse->s[parse->i]))
				parse->i++;
		}
	}
}

int	condition_append_token(t_parse *parse)
{
	if (is_end(parse))
	{
		if (!parse->is_env && parse->i - parse->idx == 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

void	parse_token_sub(t_data *data, t_parse *parse)
{
	if (!is_space(parse->s[parse->i]))
	{
		while (1)
		{
			if (condition_backslash(parse))
				continue ;
			condition_dollar(data, parse);
			condition_qout(parse);
			if (condition_append_token(parse))
			{
				append_token(data->token_list, parse, &parse->s[parse->idx], \
						parse->i - parse->idx);
				parse->i++;
				break ;
			}
			parse->i++;
		}
	}
}

void    parse_token(t_data *data, char *str)
{
	t_parse parse;

	init_parse(&parse, str);
	create_token_list(data);
	if (parse.s[parse.i])
	{
		parse.idx = parse.i;
		parse_token_sub(data, &parse);
	}
	while (parse.s[parse.i])
	{
		init_parse_sub(&parse);
		parse.idx = parse.i;
		parse_token_sub(data, &parse);
		parse.i++;
	}
}