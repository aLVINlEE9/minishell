/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:19:02 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/21 19:17:52 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


# define FALSE 0
# define TRUE 1

enum e_around{
    QOUT = 20,
    D_QOUT = 21,
    NO = 22
} ;

typedef struct s_termi
{
	struct termios	*save_t;
	struct termios	*new_t;
}				t_termi;

typedef struct s_data{
	struct s_token_list	*token_list;
	struct s_env_list	*env_list;
	struct s_termi		termi;
	int					exit_code;
	int					heredoc_is_still_alive;
}	t_data;

typedef struct s_parse{
	char	*s;
	char	q;
	int	i;
	int	in_qout;
	int	in_dollar;
    int is_cmd;
    int is_env;
    int was_quot;
	int	idx;
	int	idxq_s;
	int	idxq_e;
	int	idxd_s;
	int	idxd_e;
    size_t  buf_env_len;
    t_data  *data;
}	t_parse;

typedef struct s_token{
	char			*token;
	int				in_dollar;
	int				is_cmd;
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
    int             is_val_quot;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_env_list{
	int		count;
	t_env	*head;
	t_env	*tail;
}	t_env_list;

/*
*** node ***
*/
t_env	    *search_env(t_env_list *list, char *key);
int		    create_env_list_sub(t_env_list *list);
void	    create_env_list(t_data *data);
void	    append_env_sub(t_env_list *list, t_env *new_node);
int		    append_env(t_env_list *list, char *key, char *val, int is_val_quot);
t_env	    *create_env(char *key, char *val, int is_val_quot);
t_token	    *search_token(t_token_list *list, char *token);
int		    create_token_list_sub(t_token_list *list);
void	    create_token_list(t_data *data);
void	    append_token_sub(t_token_list *list, t_token *new_node);
int		    append_token(t_token_list *list, t_parse *parse, char *token, size_t size);
t_token	    *create_token(char *token, t_parse *parse);

/*
*** parse ***
*/
void		replace_util_sub1(t_parse *parse, char *first, char *val, char *last);
void		replace_util_sub2(t_parse *parse, char *buf_start, char *buf_env, char *buf_end);
void	    replace_dollar_options(t_data *data, t_parse *parse, char *buf_start, char *buf_end);
void		replace_util(t_data *data, t_parse *parse, int idx, int start);
void		replace_dollar_to_env(t_data *data, t_parse *parse);
void        update_shlvl(t_data *data);
void	    parse_env(char **envp, t_data *data);
int		    condition_append_token(t_parse *parse);
void	    condition_dollar(t_data *data, t_parse *parse);
void	    condition_qout(t_parse *parse);
int		    condition_break(t_parse *parse);
int		    is_space(char c);
int		    is_null(char c);
int 	    is_quot(char c);
int		    is_dollar(char c);
int		    is_num(char c);
int		    is_dollar_option(char *str);
int		    is_specifier(t_parse *parse, int check);
int		    is_end(t_parse *parse);
void	    remove_char_from_idx(char *s, int idx);
void	    remove_string(char *s, int idx_s, int idx_e);
void	    qout_remove(t_parse *parse);
void        init_parse(t_data *data, t_parse *parse, char *str);
void	    init_parse_sub(t_parse *parse);
void	    parse_token_sub(t_data *data, t_parse *parse);
int		    parse_token(t_data *data, char *str);
int 	    syntax_newline(char *token);
int 	    syntax_pipe(char *token);
int		    syntax_check(t_data *data);

/*
*** utils ***
*/

size_t	    ft_strlen(const char *s);
char	    *ft_strdup(const char *src);
char	    *ft_strjoin(char const *s1, char const *s2);
char	    *ft_strjoin_jh(char const *s1, char const *s2);
int	        is_firstcmd_builtin(char *s);
void	    *ft_memmove(void *dst, const void *src, size_t num);
int	        ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	    ft_strlcpy(char *dst, const char *src, size_t size);
size_t      ft_strlcpycpy(char *dst, const char *src, size_t size);
int	        count_word(char const *s, char c);
int	        put_word(char **ret, char const *s, int wordn, char c);
char	    **go_free(char **ret, int wordn);
char	    **ft_make_split(char **ret, char const *s, char c);
char	    **ft_split(char const *s, char c);
int			is_heredoc_here(t_token **cmd_ary);
long long	ft_atol(const char *str);
void	    make_string_itoa(char *p, long long n, int len);
int	        find_len_itoa(long long n);
char	    *ft_itoa(int n);
char	    *ft_0_string(void);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
void	    *ft_memchr(const void *s, int c, size_t n);
char	    *ft_strchr(const char *s, int c);
char	    *find_first_cmd(t_token **cmd_ary);





void	sig_handler_fork_c(int signal);
void	sig_handler_fork_d(int signal);
void	sig_handler_fork_b(int signal);
void		pipex(t_data *data, char **envp);
void		exe_fork(t_token ***cmd_lst, struct s_env_list *env_lst, t_data *data);
void		exe_cmd(t_token **cmd_ary, t_data *data, int *fd, int flag);
char		**make_inout_cmd(t_token **cmd_ary, int *fd, t_data *data);
void		modify_inout(t_token **cmd_ary, int count, int *fd, t_data *data);
void		cmd_leftarrow(char *s, int *fd);
void		cmd_rightarrow(char *s, int *fd);
void		cmd_doub_leftarrow(char *s, int *fd, t_data *data);
void		cmd_doub_rightarrow(char *s, int *fd);
void		ft_iofile(char *s, int *fd, int count);
char		*ft_strjoin_jh(char const *s1, char const *s2);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int		is_alpha(char c);
int		is_alnum(int c);

typedef struct s_cmd_make
{
	int					count;
	struct s_cmd_make	*next;
}					t_cmd_make;

typedef struct s_intset_jh
{
	int	*count;
	int	*save_c;
}				t_intset_jh;

typedef struct s_dollar_str
{
	char	*str;
	int		*fd_temp;
}				t_dollar_str_jh;

void	set_termi(struct s_termi *termi);
void	termi_old(struct s_termi termi, int fd);
void	termi_new(struct s_termi termi, int fd);
void	sig_handler(int signal);
void	set_signal(void);
void	print_error(char *s, int n);
void	print_built_error(char *s1, char *s2, char *s3);
char	*dollarparsing(char *s, int count, int save_c, t_data *data);
char	*ft_substr(char const*s, unsigned int start, size_t len);
int		parse_dollar2(char *temp, char **ret, struct s_intset_jh save, t_data *data);
void	parse_dollar(char *temp, char **ret, struct s_intset_jh save, t_data *data);
int		parse_dollar2_b(char *temp, char **ret, int count, int save_c);
void	parse_backslash(char *temp, char **ret, struct s_intset_jh save, int *bs);
void	cmd_heredoc_write(struct s_dollar_str t, char *ret, char *s, t_data *data);
char	*ft_null_string(void);
void	monitoring(t_data *data, int pid, int *fd);
void	exe_cmd2(char **cmd, t_data *data);
char	**make_cmd(t_token **cmd_ary, int cmd_arg_c);
void	ft_lstadd_back(t_cmd_make **lst, t_cmd_make *new);
t_cmd_make	*ft_lstnew(int c);
void	free_cmdmake(t_cmd_make **lst);
void	free_cmdlst(t_token ***lst);
t_token	***make_t_cmd_make_lst(t_token_list *tok_lst, t_cmd_make **start, int a, int b);
void	whatisit(t_token_list *t, t_token ***cmd_l, t_cmd_make *start, t_token **temp_list);
t_token	***make_cmd_list_pipe(t_token_list *t);
void	ft_iofile2(char *s, int *fd, int count, char *filename);
int		parse_dollar_question(char **ret, t_data *data);
int		check_builtin(t_token **cmd, t_data *data);
void	built_exit(char **cmd2, int flag, t_data *data);
void	built_pwd(t_data *data);
void	built_echo(char **cmd2);
void	built_cd(char **cmd2, t_data *data);
int		ft_is_digit(char *cmd);
void	change_env(t_env_list *env_list, t_env *env, char *change_val);
void	insert_env(char **envp, char *key, char *change_val);
char    **update_env(t_data *data, int flag);
void	free_env(char **temp);
void    built_export(t_data *data, char	**cmd2);
void	built_env(t_data *data);
void	built_unset(t_data *data, char **cmd2);
void    print_env(t_env_list *env_list);
int		is_slash(char *s);
int		chk_builtin_infork(char **cmd, t_data *data);
char	*find_first_cmd(t_token **cmd);
int		is_firstcmd_builtin(char *s);
int		is_heredoc_here(t_token **cmd_ary);
void	sig_handler_fork_c(int signal);
void	sig_handler_fork_d(int signal);
void	sig_handler_fork_b(int signal);
#endif
