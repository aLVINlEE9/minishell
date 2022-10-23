/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:13:16 by seungsle          #+#    #+#             */
/*   Updated: 2022/10/23 16:10:41 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_env(t_data *data)
{
	char	**temp;
	int		i;

	temp = update_env(data, 0);
	i = 0;
	while (temp[i])
	{
		printf("%s\n", temp[i++]);
	}
	data->exit_code = 0;
	free_env(temp);
}
