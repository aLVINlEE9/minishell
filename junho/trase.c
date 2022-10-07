/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:47:21 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/07 21:03:34 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

char	*transe_str2(char *str)
{
	t_list	temp;
	temp.content = (void *)str;
	temp.str_type = 0;

	transe_str(&temp);
	return ((char *)(temp.content));
}

void	transe_str(t_list *token)
{
	if (token -> str_type == 0 || token -> str_type == 1)
		translate(token);
}

void	translate(t_list *token)
{
	char	*temp;
	int		len;

	len = 0;
	temp = (char *)(token -> content);
	printf("%s\n",temp);
	while (*(temp + len))
	{
		if (*(temp + len) == 92)
		{
			if (*(temp + len + 1) == '"' || *(temp + len + 1) == '\'' || *(temp + len + 1) == 92)
				len = backslash(token, temp, len);
			else
			{
				backslash(token, temp, len);
				len ++;
			}
		/*
		if (*(temp + len) == '$')
			dollar();
		*/
		}
		else
			len ++;
		temp = (char *)(token -> content);
		/*if (*(temp+ len) == 92)
			len ++;
			*/
	}
}

int	backslash(t_list *token, char *str, int len)
{
	char	*front;
	char	*back;
	char	*save;
	char	*ret;

	save = str;
	front = ft_substr(str, 0, len);
	back = ft_substr(str, len + 1, ft_strlen(str) - (len));
	ret = ft_strjoin(front, back);
	token -> content = (void *)(ret);
	len = ft_strlen(front);
	free(front);
	free(back);
	free(save);

	return (len + 1);
}
