/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:32:26 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/14 20:20:26 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dollarparsing(char *s, int count, int save_c)
{
	char	*save;
	char	*ret;
	char	*temp;
	int		back_slash;

	ret= 0;
	parse_dollar(s, &ret, &count, &save_c);
	temp = s;
	if (save_c != count)
	{
		temp = ft_substr(temp, save_c, -1);
		ret = ft_strjoin_jh(ret, temp);
	}
	return (ret);
}

void	parse_dollar(char *temp, char **ret, int *count, int *save_c)
{
	int					back_slash;
	struct s_intset_jh	save_int;

	back_slash = 0;
	save_int.count = count;
	save_int.save_c = save_c;
	while (temp[*count])
	{
		if (temp[*count] == '\\')
			parse_backslash(temp, ret, save_int, &back_slash);
		else if (temp[*count] == '$')
		{
			if (back_slash == 0)
				*count += parse_dollar2(temp, ret, *count, *save_c) + 1;
			else
				*count += parse_dollar2_b(temp, ret, *count, *save_c) + 1;
			*save_c = *count;
		}
		else
		{
			back_slash = 0;
			(*count) ++;
		}
	}
}

void	parse_backslash(char *temp, char **ret, struct s_intset_jh save, int *back_slash)
{
	if (*back_slash == 1)
	{
		*ret = ft_strjoin(*ret, ft_substr(temp, *(save.save_c), *(save.count)\
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
	while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1])\
			 && temp[ct + count + 1] != '"' && temp[ct + count + 1] != '\''\
			  && temp[ct + count + 1] != '\\')
		ct ++;
	find_str = ft_substr(temp, count, ct + 1);
	*ret = ft_strjoin(*ret, find_str);
	return (ct);

}

int	parse_dollar2(char *temp, char **ret, int count, int save_c)
{
	char	*pathvar;
	char	*find_str;
	int		ct;

	if (count == 0)
		;
	else if (!(*ret))
		*ret = ft_substr(temp, 0, count);
	else
		*ret = ft_strjoin(*ret, ft_substr(temp, save_c, count - save_c));
	ct = 0;
	while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1])\
			 && temp[ct + count + 1] != '"' && temp[ct + count + 1] != '\''\
			  && temp[ct + count + 1] != '\\')
		ct ++;
	find_str = ft_substr(temp, count + 1, ct);
	pathvar = getenv(find_str);
	*ret = ft_strjoin(*ret, pathvar);
	return (ct);
}
