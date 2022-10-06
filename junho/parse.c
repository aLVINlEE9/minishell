/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:11:37 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/06 22:38:45 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokenize.h"

int main ()
{
	char *str;
	
	t_list	*token_list;
	t_list	*temp;


	token_list = 0;
	str = readline("minishell$ ");// 컴파일시 -lreadline 추가
	if (str)
		tokenize(&token_list, str);
	temp = token_list;
	add_history(str);
	int count = 1;
	while (temp)
	{
		printf("%s\n", (char *)(temp -> content));
		temp = temp -> next;
		count ++;
	}
	free(str);
	return (0);
}

int	parse_double_q(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	save = temp + 1;
	count = 0;
	temp ++;
	while (*temp)
	{
		if (*temp == '"')
			break ;
		count ++;
		temp ++;
	}
	if (!(*temp))
		return (-1);//error no "
	*temp = 0;
	if (count == 0)
		return (count);
	if (flag == 0)
	{
		ret = ft_strdup(save);
		node = ft_lstnew((void *) ret);
		ft_lstadd_back(token_list, node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			ret = ft_strdup(save);
			node = ft_lstnew((void *) ret);
			ft_lstadd_back(token_list, node);
			return (count);
		}
		node = ft_lstlast(*token_list);
		ret = (node -> content);
		node -> content = (void *)(ft_strjoin((char *)(node -> content), save));
		free(ret);
	}
	return (count);
}

int	parse_single_q(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	save = temp + 1;
	count = 0;
	temp ++;
	while (*temp)
	{
		if (*temp == 39)
			break ;
		count ++;
		temp ++;
	}
	if (!(*temp))
		return (-1);//error no "
	*temp = 0;
	if (count == 0)
		return (count);
	if (flag == 0)
	{
		ret = ft_strdup(save);
		node = ft_lstnew((void *) ret);
		ft_lstadd_back(token_list, node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			ret = ft_strdup(save);
			node = ft_lstnew((void *) ret);
			ft_lstadd_back(token_list, node);
			return (count);
		}
		node = ft_lstlast(*token_list);
		ret = (node -> content);
		node -> content = (void *)(ft_strjoin((char *)(node -> content), save));
		free(ret);
	}
	return (count);
}

int parse_pipe(char *temp, t_list **token_list)
{
	t_list	*node;
	int		count;
	char	*ret;
	
	count = 0;
	temp ++;
	ret = malloc(sizeof(char) * 2);
	if (!ret)
		return (0);
	ret[0] = '|';
	ret[1] = 0;
	node = ft_lstnew((void *) ret);
	ft_lstadd_back(token_list, node);
	return (0);
}

int	parse_another(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	save = temp;
	count = 0;
	while (*temp)
	{
		if (*temp == 39 || *temp == '|' || *temp == '<' || *temp == '>' || *temp == '"')
			break ;
		count ++;
		temp ++;
	}
	ret = ft_substr(save, 0, count);
	if (flag == 0)
	{
		node = ft_lstnew((void *) ret);
		ft_lstadd_back(token_list, node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			node = ft_lstnew((void *) ret);
			ft_lstadd_back(token_list, node);
			return (count);
		}
		node = ft_lstlast(*token_list);
		save = node -> content;
		node -> content = (void *)(ft_strjoin((char *)(node -> content), ret));
		free(ret);
		free(save);
	}
	return (count);
}
