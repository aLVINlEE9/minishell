/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:37:35 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 11:38:19 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dollar_option(char *str)
{
	if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "$$", 2) == 0)
		return (2);
	return (0);
}


int	is_specifier(t_parse *parse, int check)
{
	char	c;

	c = parse->s[parse->i + check];
	if (ft_strncmp(&parse->s[parse->i + check], "<<", 2) == 0 || \
		ft_strncmp(&parse->s[parse->i + check], ">>", 2) == 0)
		return (2);
	else if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_end(t_parse *parse)
{
	if (!parse->in_qout)
	{
		if (is_null(parse->s[parse->i + 1]) || \
			is_space(parse->s[parse->i + 1]) || \
			is_specifier(parse, 1))
			return (1);
	}
	return (0);
}