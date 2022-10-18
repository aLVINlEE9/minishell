/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/18 17:55:31 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_dollar_question(char **ret , struct s_data_env *data_env)
{
	char	*temp;

	temp = ft_itoa(data_env->data->exit_code);
	*ret = ft_strjoin(*ret, temp);
	return (1);
}
