/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/06 23:32:04 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_data{
	struct s_cmd_list	*cmd_list;
	struct s_env_list	*env_list;
}	t_data;

typedef struct s_cmd{
	char			*cmd;
	int				dollar;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmd_list{
	int		count;
	t_cmd	*head;
	t_cmd	*tail;
}	t_cmd_list;

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

void    parse_cmd(t_data *data, char *str);

t_cmd	*search_cmd(t_cmd_list *list, char *cmd);
int	create_cmd_list_sub(t_cmd_list *list);
void	create_cmd_list(t_data *data);
void	append_cmd_sub(t_cmd_list *list, t_cmd *new_node);
int	append_cmd(t_cmd_list *list, char *cmd, size_t size, int dollar);
t_cmd	*create_cmd(char *cmd, int dollar);

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