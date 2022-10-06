/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:07:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/06 21:48:38 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	*ft_strjoin(char const *s1, char const *s2);
t_list	*ft_lstlast(t_list *lst);
char	*ft_strdup(const char *s1);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		parse_double_q(char *temp, t_list **token_list, int flag);
int		parse_single_q(char *temp, t_list **token_list, int flag);
int		parse_another(char *temp, t_list **token_list, int flag);
int		parse_pipe(char *temp, t_list **token_list);
int		tokenize(t_list **token_list, char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
