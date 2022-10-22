/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:50 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/22 15:27:24 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env(t_data *data)
{
	char	**temp;
	int	i;

	temp = update_env(data, 0);
	i = 0;
	while (temp[i])
	{
		printf("%s\n", temp[i++]);
	}
	data->exit_code = 0;
}

void	built_unset(t_data *data, char **cmd2)
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
		env = search_env(data->env_list, cmd2[i]);
		if (!env)
			continue ;
		else
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
			env->next = 0;
			env->prev = 0;
			free(env->val);
			free(env->key);
			free(env);	
		}
	}
}