/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:07:50 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/07 20:18:52 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_data{
	struct s_env_list	*env_list;
}	t_data;

typedef struct s_env{
	char			*key;
	char			*val;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_env_list{
	int		count;
	t_env	*head;
	t_env	*tail;
}	t_env_list;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				str_type;
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
int		parse_right_arrow(char *temp, t_list **token_list, int flag);
int		parse_left_arrow(char *temp, t_list **token_list, int flag);
int		parse_between_arrow(char *temp, t_list **token_list, int flag);
int		tokenize(t_list **token_list, char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen(const char *s);
void	transe_str(t_list *token_list);
void	translate(t_list *token_list);
int		backslash(t_list *token_lsit, char *str, int len);
void    update_shlvl(t_data *data);
void    parse_env(char **envp, t_data *data);

t_env	*search_env(t_env_list *list, char *key);
int	create_env_list_sub(t_env_list *list);
void	create_env_list(t_data *data);
void	append_env_sub(t_env_list *list, t_env *new_node);
int	append_env(t_env_list *list, char *key, char *val);
t_env	*create_env(char *key, char *val);

int	count_word(char const *s, char c);
int	put_word(char **ret, char const *s, int wordn, char c);
char	**go_free(char **ret, int wordn);
char	**ft_make_split(char **ret, char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
long long	ft_atol(const char *str);
void	make_string_itoa(char *p, long long n, int len);
int	find_len_itoa(long long n);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
