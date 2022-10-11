/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:23:00 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/11 18:09:27 by seungsle         ###   ########.fr       */
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

int	condition_specifier(t_parse *parse)
{
	if (is_specifier(parse) == 1 || is_specifier(parse) == 2)
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

int	condition_append_token(t_parse *parse)
{
	if (parse->is_cmd == TRUE)
	{
		parse->i += is_specifier(parse);
		return (1);
	}
	else if ((!parse->in_qout && is_space(parse->s[parse->i])) \
			|| !parse->s[parse->i])
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

void	condition_dollar(t_parse *parse)
{

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
		condition_dollar(parse);
		condition_backslash(parse);
		condition_qout_started(parse);
		condition_qout_ended(parse);
	}
}

void	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(&parse, str);
	if (!is_space(parse.s[parse.i]) || condition_specifier(&parse))
	{
		parse.idx = parse.i;
		parse_token_sub(data, &parse);
	}
	while (parse.s[parse.i])
	{
		if ((parse.s[parse.i + 1] && is_space(parse.s[parse.i]) \
			&& !is_space(parse.s[parse.i + 1])) || parse.is_cmd)
		{
			if (!parse.is_cmd)
				parse.i++;
			init_parse_sub(&parse);
			parse.idx = parse.i;
			condition_specifier(&parse);
			parse_token_sub(data, &parse);
		}
		parse->i++;
	}
}