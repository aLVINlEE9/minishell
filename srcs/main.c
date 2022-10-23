/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:17:37 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 14:22:51 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    print_node(t_token_list *token_list)
{
    t_token *now;

    now = token_list->head->next;
    while (now != token_list->tail)
    {
        printf("%s dollar:%d cmd:%d\n", now->token, now->in_dollar, now->is_cmd);
        now = now->next;
    }
    return (1);
}

// void	parse_entt(char **env)
// {
// 	int		i;
// 	char	**ret;
// 	char	**temp;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (env[i][0] == 'S' && env[i][1] == 'H' && env[i][2] == 'L' && \
// 				env[i][3] == 'V' && env[i][4] == 'L' && env[i][5] == '=')
// 		{
// 			env[i][6] = '8';
// 		}
// 		i ++;
// 	}
// }

void    print_env(t_env_list *env_list)
{
    t_env *now;

    now = env_list->head->next;
    while (now != env_list->tail)
    {
        printf("%s ====  %s\n", now->key, now->val);
        now = now->next;
    }
}

void    free_for_line(t_data *data)
{
    t_token *now;

    now = data->token_list->head->next;
    while (now != data->token_list->tail)
    {
        free(now->token);
        free(now);
        now = now->next;
    }
    free(data->token_list->head);
    free(data->token_list->tail);
    free(data->token_list);
}

void    free_for_all(t_data *data)
{
    t_env   *now;

    now = data->env_list->head->next;
    while (now != data->env_list->tail)
    {
        free(now->key);
        free(now->val);
        free(now);
        now = now->next;
    }
    free(data->env_list->head);
    free(data->env_list->tail);
    free(data->env_list);
}

void    leak_check(void)
{
    system("leaks minishell");
}

char    **unset_oldpath(void)
{
    char    **ret;

    ret = (char **)malloc(sizeof(char *) * 3);
    ret[0] = ft_strdup("unset");
    ret[1] = ft_strdup("OLDPWD");
    ret[2] = 0;
    return (ret);
}

char    **export_oldpath(void)
{
    char    **ret;

    ret = (char **)malloc(sizeof(char *) * 3);
    ret[0] = ft_strdup("export");
    ret[1] = ft_strdup("OLDPWD");
    ret[2] = 0;
    return (ret);
}

void	free_cmd(char **cmd)
{
	free(cmd[0]);
	free(cmd[1]);
	free(cmd);
}

void	update_home(t_data *data)
{
	t_env	*env;
	char	*pwd;
	char	*oldpwd;
	char	*home;

	env = search_env(data->env_list, "HOME");
	if (env)
		data->home = ft_strdup(env->val);
	data->oldpwd = NULL;
	data->pwd = getcwd(NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	t_data      	data;
	char			**cmd;
	char        	*str;
	int				ch;
	struct s_termi	termi;

	(void)argc;
	(void)argv;
    // atexit(leak_check);
	parse_env(envp, &data); // 32 leaks
	cmd = unset_oldpath();
    built_unset(&data, cmd);
	free_cmd(cmd);
	cmd = export_oldpath();
    built_export(&data, cmd);
	free_cmd(cmd);
    // parse_entt(envp);
	//
	set_termi(&termi); // 1 1eak
	data.termi = termi;
	//
    // print_env(data.env_list);
	update_shlvl(&data); // 1 leak
	update_home(&data);
	// tcgetattr(0, &termi);
	// termi.c_lflag &= ~(ECHOCTL);
	// termi.c_lflag &= ~(ECHO);
	// tcsetattr(0, TCSANOW, &termi);
	// printf("%s %s\n", search_env(data.env_list, "SHLVL")->val, search_env(data.env_list, "SHLVL")->key);
	while (1)
	{
		set_signal();
		termi_new(data.termi, 0);
		// print_env(data.env_list);
		data.heredoc_is_still_alive = 0;
		str = readline("minishell$ ");// 컴파일시 -lreadline 추가
		if (str == 0)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			free(str);
			break ;
		}
		else if (str)
		{
			add_history(str);
			if (parse_token(&data, str))
				pipex(&data, envp);
			free_for_line(&data);
		}
		// free(str);
	}
	termi_old(data.termi, 0);
	free_for_all(&data);
}
//env 저장
//"", '' 파싱
// $ 
