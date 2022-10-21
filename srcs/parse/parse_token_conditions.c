/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_conditions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:36:35 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 16:23:09 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	condition_append_token(t_parse *parse)
{
	if (!parse->in_qout)
	{
		if ((is_null(parse->s[parse->i]) && ft_strlen(parse->s) == (parse->i)) \
			|| is_space(parse->s[parse->i]))
			return (1);
		else if (is_specifier(parse, 0))
		{
			parse->i += is_specifier(parse, 0);
			parse->is_cmd = TRUE;
			return (1);
		}
		else if (parse->s[parse->i] != '\"' && is_specifier(parse, 1))
		{
			parse->i++;
			return (1);
		}
	}
	return (0);
}

void	condition_dollar(t_data *data, t_parse *parse)
{
	if (is_dollar(parse->s[parse->i]) && !is_end(parse))
	{
		if (!parse->in_qout && is_quot(parse->s[parse->i + 1]))
			remove_char_from_idx(parse->s, parse->i);
		else if (!(parse->in_qout && parse->q == '\''))
		{
			parse->in_dollar++;
			replace_dollar_to_env(data, parse);
		}
	}
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

int	condition_break(t_parse *parse)
{
	if (!parse->was_quot && parse->i - parse->idx == 0 && \
		parse->in_dollar && !parse->is_env)
		return (1);
	if (parse->in_qout && is_null(parse->s[parse->i]))
	{
		printf("unclose quot\n");
		return (1);
	}
	return (0);
}
