/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:12:42 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:11:38 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_unset(t_data *data, char **cmd2)
{
	t_env	*env;
	t_env	*temp;
	int		i;

	i = 0;
	while (cmd2[i++])
	{
		if (!cmd2[i])
			continue ;
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
	data->exit_code = 0;
}
