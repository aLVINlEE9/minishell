/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:28:13 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/20 11:59:13 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	insert_env(char **envp, char *key, char *change_val)
// {

// }
int	is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	export_valid_check(char **cmd2, int i)
{
	if (is_alpha(cmd2[i][0]))
        return (0) ;
    else
	{
		printf("export: `%c': not a valid identifier\n", cmd2[i][0]);
		return (1);
	}
}

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

// void	print_envs(char **envs)
// {
// 	int i = 1;
// 	while (envs[i])
// 	{
// 		printf("%s %d\n", envs[i], i);
// 	}
// }

char	**sort_export(struct s_data_env *data_env)
{
	char	**envs;
	char	*temp;
	int	i;
	int	j;

	envs = update_env(data_env, 1);
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

void	print_export(struct s_data_env *data_env)
{
	char	**envs;
	char	**splited;
	t_env	*env;
	int	i;

	envs = sort_export(data_env);
	print_env(data_env->data->env_list);
	i = 0;
	while (envs[i])
	{
		splited = ft_split(envs[i], '=');
		env = search_env(data_env->data->env_list, splited[0]);
		printf("declare -x ");
		if (env->is_val_quot)
		{
			printf("%s\n", env->key);
		}
		else if (!env->val)
		{
			printf("%s=\"\"\n", env->key);
		}
		// if (!env->val)
		// {
		// 	// printf("in %d\n", env->is_val_quot);
		// 	if (env->is_val_quot == 0)
		// 		printf("%s=\"\"\n", env->key);
		// 	else
				
		// }
		else
		{
			printf("%s=\"%s\"\n", env->key, env->val);
		}
		free(splited);
		i++;
	}
	free_env(envs);
	// free_sort_export(envs);
}

void    built_export(struct s_data_env *data_env, char	**cmd2)
{
    char **splited;
	int	i;

    if (!cmd2[1])
    {
        print_export(data_env);
        return ;
    }
	i = 1;
	while (cmd2[i])
	{
		if (export_valid_check(cmd2, i))
			return ;
		if (!ft_strchr(cmd2[i], '='))
		{
			append_env(data_env->data->env_list, ft_strdup(cmd2[i]), NULL, 1);
		}
		else
		{
			splited = ft_split(cmd2[i], '=');
			append_env(data_env->data->env_list, splited[0], splited[1], 0);
		}
		i++;
	}
    
    // printf("%s\n%s\n", splited[0], splited[1]);
    // printf("%s\n%s\n%s\n", cmd2[0], cmd2[1], cmd2[2]);
}