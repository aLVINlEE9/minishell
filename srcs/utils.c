/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:36:51 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/18 19:10:29 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		return (NULL);
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
		return (NULL);
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (size_1 + size_2 + 1));
	if (!ret)
		return (NULL);
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
		return (NULL);
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (size_1 + size_2 + 1));
	if (!ret)
		return (NULL);
	ft_memmove(ret, s1, size_1);
	ft_memmove(ret + size_1, s2, size_2);
	ret[size_1 + size_2] = '\0';
	return (ret);
}

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
	if (buffer_d == NULL && buffer_s == NULL)
		return (NULL);
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

long long	ft_atol(const char *str)
{
	long long	ret;
	long long	p;

	ret = 0;
	p = 1;
	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			p *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret *= 10;
		ret += (p * (*str - '0'));
		str++;
	}
	return (ret);
}

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

void	make_string_itoa(char *p, long long n, int len)
{
	if (n / 10 == 0)
	{
		*p = (n % 10 + '0');
		return ;
	}
	make_string_itoa(p, n / 10, len - 1);
	*(p + len) = (n % 10 + '0');
}

int	find_len_itoa(long long n)
{
	int	ret;

	ret = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		ret ++;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	long long	ln;
	char		*p;
	int			len;

	ln = n;
	if (ln < 0)
		ln = -ln;
	len = find_len_itoa(ln);
	if (n >= 0)
		p = malloc(sizeof(char) * (len + 1));
	else
		p = malloc(sizeof(char) * (len + 2));
	if (!p)
		return (0);
	if (n < 0)
	{
		*p = '-';
		p ++;
	}
	*(p + len) = '\0';
	make_string_itoa(p, ln, len - 1);
	if (n < 0)
		return (--p);
	return (p);
}

char	*ft_null_string(void)
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
		return (NULL);
	while (*(s + s_len) != '\0')
		s_len ++;
	if (s_len <= start)
		return (ft_null_string());
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
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}