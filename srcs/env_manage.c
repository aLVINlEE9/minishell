/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:04:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/19 18:15:03 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_envv(struct s_data_env *data_env)
// {
// 	int i = 0;
// 	while (data_env->envp[i])
// 	{
// 		printf("%s\n", data_env->envp[i]);
// 		i++;
// 	}
// }

void	free_env(char **temp)
{
	int	i;

	i = 0;
	while(temp[i])
		free(temp[i++]);
	free(temp);
}

char    **update_env(struct s_data_env *data_env, int flag)
{
	t_env_list	*env_list;
	t_env		*env;
	char		**temp_list;
	char		*temped;
	char		*temp;
	int			i;

	env_list = data_env->data->env_list;
	env = env_list->head->next;
	temp_list = (char **)malloc(sizeof(char *) * env_list->count + 1);
	i = 0;
	// print_env(env_list);
	while (env != env_list->tail)
	{
		// printf("%s=%s\n", env->key, env->val);
		if (env->is_val_quot && !flag)
		{
			env = env->next;
			continue ;
		}
		temped = ft_strjoin(ft_strdup(env->key), "=");
		if (env->val == NULL)
			temp_list[i] = temped;
		else
			temp_list[i] = ft_strjoin(temped, ft_strdup(env->val));
		env = env->next;
		i++;
		// free(temped);
	}
	temp_list[i] = 0;
	// free(data_env->envp);
	// data_env->envp = temp_list;
	// print_envv(data_env);
	return (temp_list);
}