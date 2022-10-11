/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/11 18:31:19 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>


# define FALSE 0
# define TRUE 1

enum e_around{
    QOUT = 20,
    D_QOUT = 21,
    NO = 22
} ;

typedef struct s_data{
	struct s_token_list	*token_list;
	struct s_env_list	*env_list;
	int					exit_code;
}	t_data;

typedef struct s_parse{
	char	*s;
	char	q;
    int unclose_quot;
    int unclose_slash;
	int	i;
	int	in_qout;
	int	in_dollar;
    int is_cmd;
	int	idx;
	int	idxq_s;
	int	idxq_e;
	int	idxd_s;
	int	idxd_e;
}	t_parse;

typedef struct s_token{
	char			*token;
	int				in_dollar;
    int             is_cmd;
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
int	is_dollar_option(char *str);


t_token	*search_token(t_token_list *list, char *token);
int	create_token_list_sub(t_token_list *list);
void	create_token_list(t_data *data);
void	append_token_sub(t_token_list *list, t_token *new_node);
int	append_token(t_token_list *list, t_parse *parse, char *token, size_t size);
t_token	*create_token(char *token, t_parse *parse);

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
size_t      ft_strlcpycpy(char *dst, const char *src, size_t size);
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
void	pipex(t_data *data, char **envp);
void	exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, char **envp);
void	exe_cmd(t_token **cmd_ary, char **envp, int *fd);
char	**make_inout_cmd(t_token **cmd_ary, int *fd);
void	modify_inout(t_token **cmd_ary, int count, int *fd);
void	cmd_leftarrow(char *s, int *fd);
void	cmd_rightarrow(char *s, int *fd);
void	cmd_doub_leftarrow(char *s, int *fd);
void	cmd_doub_rightarrow(char *s, int *fd);
void	ft_iofile(char *s, int *fd, int count);

typedef struct s_cmd_make
{
	int					count;
	struct s_cmd_make	*next;
}					t_cmd_make;
#endif
