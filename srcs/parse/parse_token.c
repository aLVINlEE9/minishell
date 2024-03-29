/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:23:00 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 14:32:12 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_parse(t_data *data, t_parse *parse, char *str)
{
	parse->s = str;
	parse->q = 0;
	parse->i = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
	parse->is_dollar_option = FALSE;
	parse->idx = 0;
	parse->is_cmd = 0;
	parse->is_env = 0;
	parse->idxq_s = 0;
	parse->idxq_e = 0;
	parse->idxd_s = 0;
	parse->idxd_e = 0;
	parse->buf_env_len = 0;
	parse->data = data;
}

void	init_parse_sub(t_parse *parse)
{
	parse->is_cmd = 0;
	parse->in_qout = FALSE;
	parse->in_dollar = FALSE;
	parse->is_env = FALSE;
	parse->is_dollar_option = FALSE;
	parse->was_quot = FALSE;
	parse->buf_env_len = 0;
}

int	parse_token_sub(t_data *data, t_parse *parse)
{
	while (1)
	{
		if (condition_break(parse) == 2)
			return (1);
		if (condition_break(parse) == 1)
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
	return (0);
}

int	parse_token(t_data *data, char *str)
{
	t_parse	parse;

	init_parse(data, &parse, str);
	create_token_list(data);
	while (parse.s[parse.i])
	{
		parse.idx = parse.i;
		init_parse_sub(&parse);
		if (!is_space(parse.s[parse.i]))
			if (parse_token_sub(data, &parse))
				return (0);
		if (is_space(parse.s[parse.i]))
			parse.i++;
	}
	free(parse.s);
	if (syntax_check(data))
		return (0);
	return (1);
}
