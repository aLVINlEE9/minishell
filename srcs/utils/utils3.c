/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:16:22 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 12:17:16 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_word(char const *s, char c)
{
	int	count;
	int	len;
	int	flag;

	count = 0;
	flag = 0;
	len = 0;
	if (*s == '\0')
		return (count);
	while (*(s + len) != '\0')
	{
		if (*(s + len) != c && flag == 0)
		{
			flag = 1;
			count ++;
		}
		else if (*(s + len) == c)
			flag = 0;
		len ++;
	}
	return (count);
}

int	put_word(char **ret, char const *s, int wordn, char c)
{
	int		len;
	char	*p;

	len = 0;
	while (*(s + len) != '\0')
	{
		if (*(s + len) == c)
			break ;
		len ++;
	}
	p = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	len = 0;
	while (*(s + len) != '\0')
	{
		if (*(s + len) == c)
			break ;
		*(p + len) = *(s + len);
		len ++;
	}
	*(p + len) = '\0';
	*(ret + wordn) = p;
	return (len);
}

char	**go_free(char **ret, int wordn)
{
	while (wordn >= 0)
	{
		free(*(ret + wordn));
		wordn --;
	}
	free(ret);
	return (0);
}

char	**ft_make_split(char **ret, char const *s, char c)
{
	int	wordn;
	int	check;
	int	temp;

	temp = 0;
	wordn = 0;
	while (*(s + temp) != '\0')
	{
		if (*(s + temp) != c)
		{
			check = put_word(ret, s + temp, wordn ++, c);
			if (!check)
				return (go_free(ret, --wordn));
			temp += check - 1;
		}
		temp ++;
	}
	*(ret + wordn) = 0;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	int		wordn;
	// int		temp;
	char	**ret;

	// temp = 0;
	if (!s)
		return (0);
	wordn = count_word(s, c);
	ret = malloc(sizeof(char *) * (wordn + 1));
	if (!ret)
		return (0);
	if (!ft_make_split(ret, s, c))
		return (0);
	return (ret);
}
