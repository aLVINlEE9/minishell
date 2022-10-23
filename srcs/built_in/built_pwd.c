/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:10:06 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 15:10:12 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_pwd(t_data *data)
{
	t_env	*env;
	char	*ret;
	
	ret = getcwd(NULL, 0);
	write(1, ret, ft_strlen(ret));
	write(1, "\n", 1);
	free(ret);
	data->exit_code = 0;
}