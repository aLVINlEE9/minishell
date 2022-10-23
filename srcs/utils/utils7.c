/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:00:18 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 16:37:17 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_oldpath(void)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 3);
	ret[0] = ft_strdup("export");
	ret[1] = ft_strdup("OLDPWD");
	ret[2] = 0;
	return (ret);
}

void	free_cmd(char **cmd)
{
	free(cmd[0]);
	free(cmd[1]);
	free(cmd);
}

void	update_home(t_data *data)
{
	t_env	*env;

	env = search_env(data->env_list, "HOME");
	if (env)
		data->home = ft_strdup(env->val);
	data->oldpwd = NULL;
	data->pwd = getcwd(NULL, 0);
}
