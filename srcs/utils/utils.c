/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 19:38:34 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/22 19:40:19 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_ss(char const *s1, char const *s2)
{
	size_t			size_1;
	size_t			size_2;
	char			*ret;

	if (!s1 && !s2)
		return (0);
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (size_1 + size_2 + 1));
	if (!ret)
		return (0);
	ft_memmove(ret, s1, size_1);
	ft_memmove(ret + size_1, s2, size_2);
	ret[size_1 + size_2] = '\0';
	free((char *)s2);
	free((char *)s1);
	return (ret);
}