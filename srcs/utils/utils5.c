/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:30:06 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 13:30:10 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_0_string(void)
{
	char	*p;

	p = malloc(sizeof(char) * 1);
	if (!p)
		return (0);
	*p = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*p;
	int					count;
	unsigned int		s_len;

	count = 0;
	s_len = 0;
	if (!s)
		return (0);
	while (*(s + s_len) != '\0')
		s_len ++;
	if (s_len <= start)
		return (ft_0_string());
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	while (len && *(s + start + count) != '\0')
	{
		*(p + count) = *(s + start + count);
		len --;
		count ++;
	}
	*(p + count) = '\0';
	return (p);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_u;

	i = 0;
	s_u = (unsigned char *)s;
	while (i < n)
	{
		if (s_u[i] == (unsigned char)c)
		{
			return ((void *)(s_u + i));
		}
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

char	*find_first_cmd(t_token **cmd_ary)
{
	int	count;

	count = 0;
	while (cmd_ary[count])
	{
		if (cmd_ary[count]->is_cmd != 1)
			return (cmd_ary[count]->token);
		count ++;
	}
	return (0);
}
