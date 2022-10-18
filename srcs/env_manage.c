/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:04:24 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/18 19:36:31 by seungsle         ###   ########.fr       */
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

char    **update_env(struct s_data_env *data_env)
{
	t_env_list	*env_list;
	t_env		*env;
	char		**temp_list;
	char		*temped;
	char		*temp;
	int			i;

	env_list = data_env->data->env_list;
	env = env_list->head->next;
	temp_list = (char **)malloc(sizeof(char *) * env_list->count);
	i = 0;
	while (env != env_list->tail)
	{
		temped = ft_strjoin(env->key, "=");
		temp_list[i++] = ft_strjoin(temped, env->val);
		env = env->next;
		// free(temped);
	}
	// free(data_env->envp);
	// data_env->envp = temp_list;
	// print_envv(data_env);
	return (temp_list);
}