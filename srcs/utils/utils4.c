/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:30:17 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 12:40:06 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
