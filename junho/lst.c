/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:10:02 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/07 20:18:46 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"


void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iter;

	iter = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		new -> next = NULL;
	}
	else
	{
		while (iter -> next != NULL)
			iter = iter -> next;
		iter -> next = new;
		new -> next = NULL;
	}
	return ;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*p;

	p = malloc(sizeof(t_list) * 1);
	if (!p)
		return (0);
	if (!content)
		p -> content = NULL;
	else
		p -> content = content;
	p -> next = NULL;
	return (p);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*p;

	len = 0;
	while (*(s1 + len) != '\0')
		len ++;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (0);
	len = 0;
	while (*(s1 + len) != '\0')
	{
		*(p + len) = *(s1 + len);
		len ++;
	}
	*(p + len) = '\0';
	return (p);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != 0)
		lst = lst -> next;
	return (lst);
}

int	ft_find_len(char const *s1)
{
	int	len;

	len = 0;
	while (*(s1 + len) != '\0')
		len ++;
	return (len);
}

void	join_str(char	*dst, char const *src)
{
	int	temp;

	temp = 0;
	while (*(src + temp) != '\0')
	{
		*(dst + temp) = *(src + temp);
		temp ++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		temp;
	char	*p;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_find_len(s1);
	s2_len = ft_find_len(s2);
	temp = 0;
	p = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!p)
		return (0);
	join_str(p, s1);
	join_str(p + s1_len, s2);
	*(p + s1_len + s2_len) = '\0';
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

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (*(s + len) != '\0')
		len ++;
	return (len);
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
	int		temp;
	char	**ret;

	temp = 0;
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