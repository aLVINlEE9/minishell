/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:10:02 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/06 21:59:05 by junhjeon         ###   ########.fr       */
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
