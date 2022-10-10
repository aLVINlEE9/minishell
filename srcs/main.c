/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:17:37 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/10 16:13:45 by seungsle         ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	t_data      data;
	char        *str;

	(void)argc;
	(void)argv;
	parse_env(envp, &data);
	update_shlvl(&data);
	// printf("%s %s\n", search_env(data.env_list, "SHLVL")->val, search_env(data.env_list, "SHLVL")->key);
	while (1)
	{
		str = readline("minishell$ ");// 컴파일시 -lreadline 추가
		if (str)
			printf("%s\n", str);//str을 넘겨서 파싱
		else
			break ;
		add_history(str);
		parse_token(&data, str);
		print_node(data.token_list);
		free(str);
	}
}
//env 저장
//"", '' 파싱
// $ 