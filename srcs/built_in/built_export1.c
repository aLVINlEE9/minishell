/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:11:51 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:30:09 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_sort_export(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		free(envs[i]);
		i++;
	}
	free(envs);
}

char	**sort_export(t_data *data)
{
	char	**envs;
	char	*temp;
	int		i;
	int		j;

	envs = update_env(data, 1);
	i = 0;
	while (envs[i])
	{
		j = i;
		while (envs[j])
		{
			if (ft_strncmp(envs[i], envs[j], -1) > 0)
			{
				temp = envs[i];
				envs[i] = envs[j];
				envs[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envs);
}

void	print_export(t_data *data)
{
	char	**envs;
	char	**splited;
	t_env	*env;
	int		i;

	envs = sort_export(data);
	i = 0;
	while (envs[i])
	{
		splited = ft_split(envs[i], '=');
		env = search_env(data->env_list, splited[0]);
		printf("declare -x ");
		if (env->is_val_quot)
			printf("%s\n", env->key);
		else if (!env->val)
			printf("%s=\"\"\n", env->key);
		else
			printf("%s=\"%s\"\n", env->key, env->val);
		free(splited[0]);
		free(splited[1]);
		free(splited);
		i++;
	}
	free_env(envs);
}

void	built_export_sub(char *ptr, t_data *data, char **cmd2, int i)
{
	char	*key;

	if (!ptr)
	{
		append_env(data->env_list, ft_strdup(cmd2[i]), NULL, 1);
	}
	else
	{
		key = (char *)malloc(sizeof(char) * (ptr - cmd2[i] + 1));
		ft_strlcpy(key, cmd2[i], ptr - cmd2[i] + 1);
		append_env(data->env_list, key, ft_strdup(ptr + 1), 0);
	}
}

void	built_export(t_data *data, char	**cmd2)
{
	char	*ptr;
	int		i;

	if (!cmd2[1])
	{
		print_export(data);
		return ;
	}
	i = 1;
	while (cmd2[i])
	{
		ptr = ft_strchr(cmd2[i], '=');
		if (export_valid_check(cmd2, i, ptr))
		{
			data->exit_code = 1;
			return ;
		}
		built_export_sub(ptr, data, cmd2, i);
		i++;
	}
	data->exit_code = 0;
}
