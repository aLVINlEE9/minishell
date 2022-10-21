/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:32:26 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 18:39:24 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollarparsing(char *s, int count, int save_c, t_data *data)
{
	char				*save;
	char				*ret;
	char				*temp;
	struct s_intset_jh	intset;

	ret = 0;
	intset.count = &count;
	intset.save_c = &save_c;
	parse_dollar(s, &ret, intset, data);
	temp = s;
	if (save_c != count)
	{
		temp = ft_substr(temp, save_c, -1);
		ret = ft_strjoin_jh(ret, temp);
	}
	return (ret);
}

void	parse_dollar(char *temp, char **ret, struct s_intset_jh save, t_data *data)
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
				*(save.count) += parse_dollar2(temp, ret, save, data) + 1;
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

int	parse_dollar2(char *temp, char **ret, struct s_intset_jh save, t_data *data)
{
	t_env	*env;
	char	*find_str;
	int		ct;
	int		count;

	count = *(save.count);
	//printf("count : %d\n", count);
	//if (count == 0)
		//;
	/*else*/ if (!(*ret))
		*ret = ft_substr(temp, 0, count);
	else
		*ret = ft_strjoin(*ret, ft_substr(temp, *(save.save_c), *(save.count) - *(save.save_c)));
	ct = 0;
	if (temp[count + 1] == '?')
		return (parse_dollar_question(ret, data));
	while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1]) \
			&& temp[ct + count + 1] != '"' && temp[ct + count + 1] != '\'' \
			&& temp[ct + count + 1] != '\\')
		ct ++;
	find_str = ft_substr(temp, count + 1, ct);
	env = search_env(data->env_list, find_str);
	if (env)
		*ret = ft_strjoin(*ret, env->val);
	else
		*ret = ft_strjoin(*ret, "");
	return (ct);
}
