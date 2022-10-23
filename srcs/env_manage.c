/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:04:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:36:55 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
		free(temp[i++]);
	free(temp);
}

void	update_env2(t_env *env, t_env_list *env_list, \
		int flag, char **temp_list)
{
	int		i;
	char	*temped;

	i = 0;
	while (env != env_list->tail)
	{
		if (env->is_val_quot && !flag)
		{
			env = env->next;
			continue ;
		}
		temped = ft_strjoin(ft_strdup(env->key), "=");
		if (env->val == NULL)
			temp_list[i] = temped;
		else
			temp_list[i] = ft_strjoin_ss(temped, ft_strdup(env->val));
		env = env->next;
		i++;
	}
	temp_list[i] = 0;
	return ;
}

char	**update_env(t_data *data, int flag)
{
	t_env_list	*env_list;
	t_env		*env;
	char		**temp_list;

	env_list = data->env_list;
	env = env_list->head->next;
	temp_list = (char **)malloc(sizeof(char *) * env_list->count + 1);
	update_env2(env, env_list, flag, temp_list);
	return (temp_list);
}
