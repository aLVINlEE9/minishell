/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhjeon <junhjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/17 16:59:38 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_dollar_question(char **ret , struct s_data_env data_env)
{
	char	*temp;

	temp = ft_itoa(data_env.data->exit_code);
	*ret = ft_strjoin(*ret, temp);
	return (1);
}
