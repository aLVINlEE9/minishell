/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:11:37 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/07 19:24:20 by junhjeon         ###   ########.fr       */
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
	while(1)
	{
	str = readline("minishell$ ");// 컴파일시 -lreadline 추가
	if (str)
		tokenize(&token_list, str);
	temp = token_list;
	add_history(str);
	int count = 0;
	while (temp)
	{
		printf("%s\n", (char *)(temp -> content));
		temp = temp -> next;
		count ++;
	}
	free(str);
	token_list = 0; // leak 나중에 지워야함
	}
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
		{
			if (*(temp - 1) != 92)//backslash
				break ;
		}
		count ++;
		temp ++;
	}
	if (!(*temp))
		return (-1);//error no "
	*temp = 0;
	if (count == 0)
		return (count);
	if (flag == 0 || flag == 2)
	{
		ret = ft_strdup(save);
		node = ft_lstnew((void *) ret);
		node -> str_type = 1;
		ft_lstadd_back(token_list, node);
		transe_str(node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			ret = ft_strdup(save);
			node = ft_lstnew((void *) ret);
			node -> str_type = 1;
			ft_lstadd_back(token_list, node);
			transe_str(node);
			return (count);
		}
		node = ft_lstlast(*token_list);
		node -> str_type = 1;
		ret = (node -> content);
		node -> content = (void *)(ft_strjoin((char *)(node -> content), save));
		free(ret);
		transe_str(node);
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
	if (flag == 0 || flag == 2)
	{
		ret = ft_strdup(save);
		node = ft_lstnew((void *) ret);
		node -> str_type = 2;
		ft_lstadd_back(token_list, node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			ret = ft_strdup(save);
			node = ft_lstnew((void *) ret);
			node -> str_type = 2;
			ft_lstadd_back(token_list, node);
			return (count);
		}
		node = ft_lstlast(*token_list);
		node -> str_type = 2;
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
	char	*save;

	count = 0;
	save = temp;
	while (*temp)
	{
		if (*temp == '|')
		{
			temp ++;
			count ++;
		}
		else
			break ;
	}
	ret = ft_substr(save, 0, count);
	node = ft_lstnew((void *) ret);
	node -> str_type = 3;
	ft_lstadd_back(token_list, node);
	return (count);
}

int	parse_left_arrow(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	count = 0;
	save = temp;
	while (*temp)
	{
		if (*temp == '<')
		{
			temp ++;
			count ++;
		}
		else
			break ;
	}
	ret = ft_substr(save, 0, count);
	node = ft_lstnew((void *) ret);
	node -> str_type = 4;
	ft_lstadd_back(token_list, node);
	return (count);
}

int parse_right_arrow(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	count = 0;
	save = temp;
	while (*temp)
	{
		if (*temp == '>')
		{
			temp ++;
			count ++;
		}
		else
			break ;
	}
	ret = ft_substr(save, 0, count);
	node = ft_lstnew((void *) ret);
	node -> str_type = 5;
	ft_lstadd_back(token_list, node);
	return (count);
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
		if (*temp == 39 || *temp == '|' || *temp == '<' || *temp == '>' || *temp == '"' || \
				*temp == ' ')
			break ;
		count ++;
		temp ++;
	}
	ret = ft_substr(save, 0, count);
	if (flag == 0 || flag == 2)
	{
		node = ft_lstnew((void *) ret);
		node -> str_type = 0;
		ft_lstadd_back(token_list, node);
		//trnase_str(node);
	}
	if (flag == 1)
	{
		if (*token_list == 0)
		{
			node = ft_lstnew((void *) ret);
			node -> str_type = 0;
			ft_lstadd_back(token_list, node);
			//transe_str(node);
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

int	parse_between_arrow(char *temp, t_list **token_list, int flag)
{
	t_list	*node;
	int		count;
	char	*ret;
	char	*save;

	save = temp;
	temp ++;
	count = 1;
	while (*temp)
	{
		if (*temp == ' ')
		{
			temp ++;
			count ++;
		}
		else
			break ;
	}
	while (*temp)
	{
		if (*temp == 39 || *temp == '|' || *temp == '<' || *temp == '>' || *temp == '"' \
				 || *temp == ' ')
			break ;
		count ++;
		temp ++;
	}
	ret = ft_substr(save, 0, count);
	node = ft_lstnew((void *) ret);
	ft_lstadd_back(token_list, node);
	return (count);
}
