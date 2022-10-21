/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:36:51 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 15:04:20 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	char	*ret;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (0);
	ret = dst;
	while (*src)
	{
		*dst++ = *src++;
	}
	*dst = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
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
	free((char *)s1);
	return (ret);
}

char	*ft_strjoin_jh(char const *s1, char const *s2)
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
	return (ret);
}

int	is_firstcmd_builtin(char *s)
{
	if (ft_strncmp(s, "exit", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "echo", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "env", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "pwd", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "export", -1) == 0)
		return (1);
	else if (ft_strncmp(s, "unset", -1) == 0)
		return (1);
	else
		return (0);
}
