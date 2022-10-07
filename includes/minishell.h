/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/07 12:29:58 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

enum e_around{
    QOUT = 20,
    D_QOUT = 21,
    NO = 22
} ;

typedef struct s_data{
	struct s_token_list	*token_list;
	struct s_env_list	*env_list;
}	t_data;

typedef struct s_token{
	char			*token;
	int				around;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list{
	int		count;
	t_token	*head;
	t_token	*tail;
}	t_token_list;

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

void    update_shlvl(t_data *data);
void    parse_env(char **envp, t_data *data);

void    parse_token(t_data *data, char *str);

t_token	*search_token(t_token_list *list, char *token);
int	create_token_list_sub(t_token_list *list);
void	create_token_list(t_data *data);
void	append_token_sub(t_token_list *list, t_token *new_node);
int	append_token(t_token_list *list, char *token, size_t size);
t_token	*create_token(char *token);

t_env	*search_env(t_env_list *list, char *key);
int	create_env_list_sub(t_env_list *list);
void	create_env_list(t_data *data);
void	append_env_sub(t_env_list *list, t_env *new_node);
int	append_env(t_env_list *list, char *key, char *val);
t_env	*create_env(char *key, char *val);

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memmove(void *dst, const void *src, size_t num);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
long long	ft_atol(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	count_word(char const *s, char c);
int	put_word(char **ret, char const *s, int wordn, char c);
char	**go_free(char **ret, int wordn);
char	**ft_make_split(char **ret, char const *s, char c);
char	**ft_split(char const *s, char c);
void	make_string_itoa(char *p, long long n, int len);
int	find_len_itoa(long long n);
char	*ft_itoa(int n);

#endif