/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:13:01 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/08 15:35:05 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    update_shlvl(t_data *data)
{
    t_env   *shlvl;
    char    *val;
    
    shlvl = search_env(data->env_list, "SHLVL");
    val = ft_strdup(shlvl->val);
	shlvl->val = ft_itoa((int)ft_atol(val) + 1);
    free(val);
}

void    parse_env(char **envp, t_data *data)
{
	int		i;
	char	**temp;
	t_env   *env;

	i = 0;
	(void)env;
    create_env_list(data);
	while (envp[i])
	{
		{
			temp = ft_split(envp[i], '=');
			append_env(data->env_list, temp[0], temp[1]);
			// free(temp[0]);//key
			// free(temp[1]);//value
			// free(temp);
		}
		i ++;
	}
}