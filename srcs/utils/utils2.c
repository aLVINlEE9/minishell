/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:14:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 13:26:16 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t num)
{
	size_t			i;
	size_t			f;
	unsigned char	*buffer_s;
	unsigned char	*buffer_d;

	i = 0;
	f = 1;
	buffer_d = (unsigned char *)dst;
	buffer_s = (unsigned char *)src;
	if (buffer_d == 0 && buffer_s == 0)
		return (0);
	if (buffer_d > buffer_s)
	{
		f = -1;
		buffer_d += (num - 1);
		buffer_s += (num - 1);
	}
	while (i++ < num)
	{
		*buffer_d = *buffer_s;
		buffer_d += f;
		buffer_s += f;
	}
	return (dst);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_u;
	unsigned char	*s2_u;

	i = 0;
	s1_u = (unsigned char *)s1;
	s2_u = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (*s1_u && *s2_u && i++ < n - 1)
	{
		if (*s1_u != *s2_u)
		{
			return (*s1_u - *s2_u);
		}
		s1_u++;
		s2_u++;
	}
	return (*s1_u - *s2_u);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	temp;

	i = 0;
	if (!dst && !(char *)src)
		return (0);
	temp = ft_strlen(src);
	if (!size)
		return (temp);
	while (i + 1 < size && (char)src[i])
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (temp);
}

size_t  ft_strlcpycpy(char *dst, const char *src, size_t size)
{
    size_t	i;
	size_t	temp;

	i = 0;
	if (!dst && !(char *)src)
		return (0);
	temp = ft_strlen(src);
	if (!size)
		return (temp);
	while (i + 1 < size && (char)src[i])
	{
		dst[i] = (char)src[i];
		i++;
	}
	return (temp);
}
