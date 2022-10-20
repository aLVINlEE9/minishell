/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:32:26 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/18 17:55:21 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollarparsing(char *s, int count, int save_c, struct s_data_env *data_env)
{
	char				*save;
	char				*ret;
	char				*temp;
	struct s_intset_jh	intset;

	ret = 0;
	intset.count = &count;
	intset.save_c = &save_c;
	parse_dollar(s, &ret, intset, data_env);
	temp = s;
	if (save_c != count)
	{
		temp = ft_substr(temp, save_c, -1);
		ret = ft_strjoin_jh(ret, temp);
	}
	return (ret);
}

void	parse_dollar(char *temp, char **ret, struct s_intset_jh save, struct s_data_env *data_env)
{
	int					back_slash;

	back_slash = 0;
	while (temp[*(save.count)])
	{
		if (temp[*(save.count)] == '\\')
			parse_backslash(temp, ret, save, &back_slash);
		else if (temp[*(save.count)] == '$')
		{
			if (back_slash == 0)
				*(save.count) += parse_dollar2(temp, ret, save, data_env) + 1;
			else
				*(save.count) += parse_dollar2_b(temp, ret, *(save.count), *(save.save_c)) + 1;
			*(save.save_c) = *(save.count);
		}
		else
		{
			back_slash = 0;
			*(save.count) += 1;
		}
	}
}

void	parse_backslash(char *temp, char **ret, \
		struct s_intset_jh save, int *back_slash)
{
	if (*back_slash == 1)
	{
		*ret = ft_strjoin(*ret, ft_substr(temp, *(save.save_c), *(save.count) \
					- *(save.save_c)));
		*(save.save_c) = *(save.count) + 1;
		*back_slash = 0;
	}
	else
		*back_slash = 1;
	*(save.count) += 1;
}

int	parse_dollar2_b(char *temp, char **ret, int count, int save_c)
{
	char	*find_str;
	int		ct;

	if (count == 0)
		;
	else if (!(*ret))
		*ret = ft_substr(temp, 0, count - 1);
	else
		*ret = ft_strjoin(*ret, ft_substr(temp, save_c, count - save_c - 1));
	ct = 0;
	while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1]) \
			&& temp[ct + count + 1] != '"' && temp[ct + count + 1] != '\'' \
			&& temp[ct + count + 1] != '\\')
		ct ++;
	find_str = ft_substr(temp, count, ct + 1);
	*ret = ft_strjoin(*ret, find_str);
	return (ct);
}

int	parse_dollar2(char *temp, char **ret, struct s_intset_jh save, struct s_data_env *data_env)
{
	char	*pathvar;
	char	*find_str;
	int		ct;
	int		count;

	count = *(save.count);
	if (count == 0)
		;
	else if (!(*ret))
		*ret = ft_substr(temp, 0, count);
	else
		*ret = ft_strjoin(*ret, ft_substr(temp, *(save.save_c), *(save.count) - *(save.save_c)));
	ct = 0;
	if (temp[count + 1] == '?')
		return (parse_dollar_question(ret, data_env));
	while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1]) \
			&& temp[ct + count + 1] != '"' && temp[ct + count + 1] != '\'' \
			&& temp[ct + count + 1] != '\\')
		ct ++;
	find_str = ft_substr(temp, count + 1, ct);
	pathvar = getenv(find_str);
	*ret = ft_strjoin(*ret, pathvar);
	return (ct);
}
