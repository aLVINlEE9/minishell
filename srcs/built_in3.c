/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:28:13 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/18 19:29:31 by seungsle         ###   ########.fr       */
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

void	export_valid_check(char **cmd2)
{
	if (is_alpha(cmd2[1][0]))
        return ;
    else
        printf("export: `%c': not a valid identifier\n", cmd2[1][0]);
}

void    built_export(struct s_data_env *data_env, char	**cmd2)
{
    char **splited;

    export_valid_check(cmd2);
    // if (!ft_strchr(cmd2[1], '='))
    // {
    //     append_env(data_env->data->env_list, )
    // }
    splited = ft_split(cmd2[1], '=');
    printf("%s\n%s\n", splited[0], splited[1]);
    // printf("%s\n%s\n%s\n", cmd2[0], cmd2[1], cmd2[2]);
}