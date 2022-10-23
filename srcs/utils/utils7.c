/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:00:18 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/23 14:29:33 by junhjeon         ###   ########.fr       */
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
	char	*pwd;
	char	*oldpwd;
	char	*home;

	env = search_env(data->env_list, "HOME");
	if (env)
		data->home = ft_strdup(env->val);
	data->oldpwd = NULL;
	data->pwd = getcwd(NULL, 0);
}
