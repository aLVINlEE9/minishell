/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:50 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/20 12:02:56 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_env(struct s_data_env *data_env)
{
	char	**temp;
	int	i;

	temp = update_env(data_env, 0);
	i = 0;
	while (temp[i])
	{
		printf("%s\n", temp[i++]);
	}
}

void	built_unset(struct s_data_env *data_env, char **cmd2)
{
	t_env	*env;
	t_env	*temp;
	int	i;

	i = 0;
	while (cmd2[i++])
	{
		if (!cmd2[i])
		{
			continue ;
		}
		env = search_env(data_env->data->env_list, cmd2[i]);
		if (!env)
			continue ;
		else
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
			env->next = 0;
			env->prev = 0;
			free(env);	
		}
	}
}