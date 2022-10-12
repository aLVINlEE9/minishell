/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:17:37 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/12 22:02:13 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    print_node(t_token_list *token_list)
{
    t_token *now;

    now = token_list->head->next;
    while (now)
    {
        printf("%s dollar:%d cmd:%d\n", now->token, now->in_dollar, now->is_cmd);
        now = now->next;
    }
}

void    print_env(t_env_list *env_list)
{
    t_env *now;

    now = env_list->head->next;
    while (now != env_list->tail)
    {
        printf("%s\n", now->key);
        now = now->next;
    }
}

int main(int argc, char **argv, char **envp)
{
	t_data      	data;
	char        	*str;
	int				ch;
	struct s_termi	termi;

	(void)argc;
	(void)argv;
	parse_env(envp, &data);
	set_termi(termi);
    // print_env(data.env_list);
	update_shlvl(&data);
	//tcgetattr(0, &termi);
	//termi.c_lflag &= ~(ECHOCTL);
	//termi.c_lflag &= ~(ECHO);
	//tcsetattr(0, TCSANOW, &termi);
	set_signal();
	// printf("%s %s\n", search_env(data.env_list, "SHLVL")->val, search_env(data.env_list, "SHLVL")->key);
	while (1)
	{
		
		str = readline("minishell$ ");// 컴파일시 -lreadline 추가
		if (str == 0)
		{
			printf("\033[1A");
            printf("\033[10C");
			printf(" exit\n");
			exit(0);
		}
		else if (str)
		{
			add_history(str);
			parse_token(&data, str);
			print_node(data.token_list);
			pipex(&data, envp);
			free(str);
		}
	}
}
//env 저장
//"", '' 파싱
// $ 
