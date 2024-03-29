/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/22 18:34:47 by junhjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_dollar_question(char **ret, t_data *data)
{
	char	*temp;

	temp = ft_itoa(data->exit_code);
	*ret = ft_strjoin(*ret, temp);
	return (1);
}
