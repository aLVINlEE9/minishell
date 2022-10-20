/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dol_jh2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungsle <seungsle@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:40:33 by junhjeon          #+#    #+#             */
/*   Updated: 2022/10/20 18:50:30 by seungsle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_dollar_question(char **ret , t_data *data)
{
	char	*temp;

	temp = ft_itoa(data->exit_code);
	*ret = ft_strjoin(*ret, temp);
	return (1);
}
