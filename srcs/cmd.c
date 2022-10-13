/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:30:58 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/13 22:54:43 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*dollarparsing(char *s);

char	*dollarparsing(char *s)
{
	char	*temp;
	char	*save;
	char	*pathvar;
	char	*find_s;
	char	*ret;
	int		count;
	int		ct;
	int		save_c;

	count = 0;
	save_c = 0;
	ret= 0;
	temp = s;
	while (temp[count])
	{
		if (temp[count] == '$')
		{
			if (!ret && count != 0)
				ret = ft_substr(temp, 0, count);
			ct = 0;
			while (temp[ct + count + 1] != ' ' && (temp[ct + count + 1]) && temp[ct + count + 1] != '"'\
					 && temp[ct + count + 1] != '\'')
			{
				ct ++;
			}
			find_s = ft_substr(temp, count + 1, ct);
			pathvar = getenv(find_s);
			ret = ft_strjoin(ret, pathvar);
			count += (ct + 1);
			save_c = count;
		}
		else
			count ++;
	}
	if (save_c != count)
	{
		temp = ft_substr(temp, save_c, ft_strlen(temp));
		ret = ft_strjoin_jh(ret, temp);
	}
	return (ret);
}

void	cmd_leftarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 1);
}

void	cmd_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 0);
}

void	cmd_doub_leftarrow(char *s, int *fd)
{
	char	*str;
	char	*ret;
	int		temp[2];

	pipe(temp);
	dup2(fd[3], 0);
	while (1)
	{
		str = readline("> ");
		if (str == 0)
		{
			write(2, "\033[1A", 4);
			write(2, "\033[2C", 4);
			break ;
		}
		if (ft_strncmp(str, s, ft_strlen(s)) == 0) // 비교 함수 고쳐야함.
		{	
			free(str);
			break ;
		}
		ret = dollarparsing(str);
		if (!ret)
			write(temp[1], str, ft_strlen(str));
		else
		{
			write(temp[1], ret, ft_strlen(ret));
			free(ret);
		}
		write(temp[1], "\n", 1);
		free(str);
	}
	dup2(temp[0], 0);
	close(temp[0]);
	close(temp[1]);
	return ;
}

void	cmd_doub_rightarrow(char *s, int *fd)
{
	ft_iofile(s, fd, 2);
	return ;
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
