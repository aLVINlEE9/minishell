/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:28:13 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/21 16:22:17 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	insert_env(char **envp, char *key, char *change_val)
// {

// }
int	is_alnum(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	else if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	export_valid_check(char **cmd2, int i, char *ptr)
{
	int	j;

	j = 1;
	if (!is_alpha(cmd2[i][0]) && cmd2[i][0] != '_')
	{
		printf("export: `%s': not a valid identifier\n", cmd2[i]);
		return (1);
	}
	while (cmd2[i][j] && ptr != &cmd2[i][j])
	{
		if (!is_alnum(cmd2[i][j]) && cmd2[i][j] != '_')
		{
			printf("export: `%s': not a valid identifier\n", cmd2[i]);
			return (1);
		}
		j++;
	}
	return (0);
	// if (is_alpha(cmd2[i][0]))
    //     return (0) ;
    // else
	// {
	// 	return (1);
	// }
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

char	**sort_export(t_data *data)
{
	char	**envs;
	char	*temp;
	int	i;
	int	j;

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
	int	i;

	envs = sort_export(data);
	print_env(data->env_list);
	i = 0;
	while (envs[i])
	{
		splited = ft_split(envs[i], '=');
		env = search_env(data->env_list, splited[0]);
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

void    built_export(t_data *data, char	**cmd2)
{
	char	*key;
	char	*ptr;
	int	i;

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
			return ;
		if (!ptr)
		{
			append_env(data->env_list, ft_strdup(cmd2[i]), NULL, 1);
		}
		else
		{
			key = (char *)malloc(sizeof(char) * (ptr - cmd2[i] + 1));
			ft_strlcpy(key, cmd2[i], ptr - cmd2[i] + 1);
			// splited = ft_split(cmd2[i], '=');
			append_env(data->env_list, key, ft_strdup(ptr + 1), 0);
		}
		i++;
	}
    // printf("%s\n%s\n", splited[0], splited[1]);
    // printf("%s\n%s\n%s\n", cmd2[0], cmd2[1], cmd2[2]);
}